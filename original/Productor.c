#include "Productor.h"

const int ERROR=0;
const int ON=1;
struct buffer *buf;
int smo;
double tiempo_bloqueo;
double tiempo_consumido;
int total_mensajes;
int tamano_buffer;
double total_tiempo_espera;


int main(int argc, char **argv)
{
	Validar_Parametros(argc, argv, "Nombre Productor","Segundos");	
	int existe = Existe_Buffer(argv[1]);
	if (existe == 1) {
		if (Inicia_MemoriaCompartida(argv[1],argv[2])==ERROR) {
			perror("Error en la memoria compartida");
			exit(1);
		}
	} else {		
		printf("\nEjecute el Creador para crear el buffer '%s'\n", argv[1]);	
	}
}

int Inicia_MemoriaCompartida (const char *nombre_buffer, char *segundos) {
	srand(time(NULL));
	smo = shm_open(nombre_buffer, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (smo == -1){
		return ERROR;
	}
	buf = mmap(NULL, (sizeof(struct buffer)),
	       PROT_READ | PROT_WRITE, MAP_SHARED, smo, 0);
	if (buf == MAP_FAILED){
		return ERROR;
	}	
	tamano_buffer=buf->tamano_buffer;
	munmap(buf,sizeof(struct buffer));
	buf = mmap(NULL, (sizeof(struct buffer)+sizeof(struct list_mensajes)*tamano_buffer),
	       PROT_READ | PROT_WRITE, MAP_SHARED, smo, 0);
	if (buf == MAP_FAILED){
		return ERROR;
	}
	Inicializa_Productor(atof(segundos));
	return 1;
}

void Inicializa_Productor(double segundos){
	pid_t proceso_productor;
	float tiempo_espera;
	time_t inicio, final;
	double tiempo_consumido;
	int a;
	int estado;
	int exec =1;
	proceso_productor = getpid(); //returns the process ID (PID) of the calling process (used by routines that generate unique temporary filenames.)
		
	Asigna_Productor(proceso_productor);
	fprintf (stderr, "Nuevo productor iniciado %i \n",proceso_productor);

	while (exec){
		tiempo_espera=DistExponencial_Espera(segundos);
		fprintf(stderr,"Tiempo de espera: %f\n",tiempo_espera);
		total_tiempo_espera=total_tiempo_espera+tiempo_espera;
		sleep((int)tiempo_espera);
		estado=buf->flag_exec;
		if (estado == ON)
		{
			//semaforo de control para iniciar y finalizar el tiempo de bloqueo
			time(&inicio); 
			sem_wait(&(buf->sem1));
			sem_wait(&(buf->sem0));
			time(&final); 
			sem_getvalue(&(buf->sem2),&a);
			Crea_Mensaje(proceso_productor);
			sem_post(&(buf->sem0));
			sem_post(&(buf->sem2));
			tiempo_consumido = difftime(final,inicio);
			total_mensajes=total_mensajes+1;
			tiempo_bloqueo=tiempo_bloqueo+tiempo_consumido;
		}
		else {
			exec=0;
		}
	}
	Finaliza_Productor(proceso_productor);
}

//Asigna nuevo productor en la memoria compartida
void Asigna_Productor(int pid){
	buf->contador_productores=buf->contador_productores+1;
}

//Libera memoria y despliega
void Finaliza_Productor(int pid){
	buf->contador_productores=buf->contador_productores-1;
	munmap(buf,tamano_buffer);
	close(smo);
	Despligue_Total(pid);	
}


//Crea un nuevo mensaje en el buffer
void Crea_Mensaje(int pid){
	int posicion=buf->actual_escritura;
	int cantidad_productores=buf->contador_productores;
	int cantidad_consumidores=buf->contador_consumidores;

	int llave = Genera_Llave_Aleatoria();
	time_t current_time =time(NULL);

	buf->buffer_list[posicion].fecha_creacion=current_time;
	buf->buffer_list[posicion].llave=llave;
	buf->buffer_list[posicion].pid=pid;
	buf->buffer_list[posicion].flag_exec=ON;
	buf->actual_escritura= Genera_Posicion(posicion, buf->tamano_buffer);
	buf->mensajes_totales=buf->mensajes_totales+1;
	Despliega_Mensaje(pid,llave,current_time,posicion,cantidad_productores,cantidad_consumidores);

}

int Genera_Posicion(int posicion,int tamano_max){
	if (posicion < (tamano_max-1)){
		return posicion+1;
	}
	else{
		return 0;
	}
}


void Despliega_Mensaje(int proceso_productor,int llave,time_t fecha,int posicion,int cantidad_productores,int cantidad_consumidores){
	char buffer[20];
	struct tm * fecha1;
	fecha1 = localtime(&fecha);

	strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",fecha1);

	fprintf (stderr, "*****************************************\n");
    fprintf (stderr, "\tNuevo Mensaje en el buffer \n");
    fprintf (stderr,"\tIdentificacion del productor: %i\n",proceso_productor);
    fprintf (stderr, "\tFecha y Hora de creacion: %s\n",buffer);
    fprintf (stderr, "\tLlave: %i\n",llave);
	fprintf (stderr, "\tCantidad de productores: %i\n",cantidad_productores);
	fprintf (stderr, "\tCantidad de consumidores: %i\n",cantidad_consumidores);
	fprintf (stderr, "\tTotal acumulado de mensajes generados: %i\n",total_mensajes);
    fprintf (stderr, "\tPosicion de ingreso en el buffer: %i\n",posicion);
	fprintf (stderr, "*****************************************\n");

}

void Despligue_Total(int proceso_productor){
     fprintf (stderr, "*****************************************\n");
     fprintf (stderr, "   Fin de Ejecución Productor    \n\n");
     fprintf (stderr, "*****************************************\n");
}



