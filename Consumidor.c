
#include "Consumidor.h"

const int ERROR=0;
const int ON=1;
const int OFF=0;
struct buffer *buf;
int smo;
double tiempo_total_bloqueo;
double tiempo_total_espera; 

int key_exit;
int tamano_buffer;
int total_mensajes;
int exec=1;
// pid : process id

int main(int argc, char **argv) {
	int parameters;
	parameters=Validar_Parametros(argc, argv, "Nombre buffer","segundos");
    // falta validar si ya existe el buffer sino hay que crearlo!!!
	if ( Inicia_MemoriaCompartida(argv[1],argv[2])==ERROR){
		perror("Error en la memoria compartida");
		exit(1);
	}
}

int Inicia_MemoriaCompartida (const char *nombre_buffer, char *segundos) {
	smo = shm_open(nombre_buffer, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (smo == -1){
		return ERROR;
	}
	buf = mmap(NULL, (sizeof(struct buffer)),PROT_READ | PROT_WRITE, MAP_SHARED, smo, 0);
	if (buf == MAP_FAILED){
		return ERROR;
	}
	tamano_buffer=buf->tamano_buffer;
	munmap(buf,sizeof(struct buffer));

	buf = mmap(NULL, (sizeof(struct buffer)+sizeof(struct list_mensajes)*tamano_buffer),PROT_READ | PROT_WRITE, MAP_SHARED, smo, 0);
	if (buf == MAP_FAILED){
		return ERROR;
	}
	Inicializa_Consumidor(atof(segundos));
	return 1;
}

void Inicializa_Consumidor(double segundos){

	pid_t proceso_productor;
	float tiempo_espera;
	time_t inicio, final;
	double tiempo_consumido1, tiempo_consumido2;
	int a;
	int estado;
	int exec =1;
	proceso_productor = getpid(); //returns the process ID (PID) of the calling process (used by routines that generate unique temporary filenames.)
	

	Asigna_Consumidor(proceso_productor);
	fprintf (stderr, "Nuevo consumidor iniciado: %i \n", proceso_productor);
	while (exec){
		tiempo_espera=DistExponencial_Espera(segundos);
        fprintf(stderr,"Espera: %f\n",tiempo_espera);
        tiempo_total_espera=tiempo_total_espera+tiempo_espera;
        sleep((int)tiempo_espera);
		time(&inicio); //inicia tiempo de bloqueo
			//semaforo de control para iniciar y finalizar el tiempo de bloqueo
	        sem_wait(&(buf->sem2));
	        sem_wait(&(buf->sem0));
		  	time(&final); //finaliza tiempo de bloqueo
		  	sem_getvalue(&(buf->sem2),&a);
			Crea_Mensaje(proceso_productor);
			sem_post(&(buf->sem0));
		    sem_post(&(buf->sem1));
		    tiempo_consumido2 = difftime(final,inicio);
			total_mensajes=total_mensajes+1;
		    tiempo_total_bloqueo=tiempo_total_bloqueo+tiempo_consumido2;
	}
	Finaliza_Consumidor(proceso_productor);
}

//Asigna un nuevo productor en la memoria compartida
void Asigna_Consumidor(int pid){
	buf->contador_consumidores=buf->contador_consumidores+1;
	buf->consumidores_totales=buf->consumidores_totales+1;
}


//Liberar o suspende la memoria y despliega estadisticas
void Finaliza_Consumidor(int proceso){
	buf->contador_consumidores=buf->contador_consumidores-1;
	munmap(buf,tamano_buffer);
	close(smo);
	Imprime_Stats(proceso);
}

//Crea un nuevo mensaje en el buffer
void Crea_Mensaje(int proceso){
	time_t current_time;
	int prod_pid,llave;
	int cantidad_productores=buf->contador_productores;
	int cantidad_consumidores=buf->contador_consumidores;
	int posicion=buf->actual_lectura;
	int pos_write=buf->actual_escritura;
	current_time=buf->buffer_list[posicion].fecha_creacion;
	llave=buf->buffer_list[posicion].llave;
	prod_pid=buf->buffer_list[posicion].pid;
	if ((buf->buffer_list[posicion].flag_exec)==OFF){
		exec=OFF;
	}
	Despliega_Mensaje( prod_pid,  llave, current_time,  posicion,cantidad_productores,cantidad_consumidores);
	buf->actual_lectura=  Genera_Posicion(posicion, buf->tamano_buffer);
	if (Valida_PID (llave, proceso)==OFF){
		exec=OFF;
	}

}

void Despliega_Mensaje(int process, int llave, time_t fecha,int posicion, int cantidad_productores, int cantidad_consumidores){
	char buffer[20];
	struct tm * time1;
	time1 = localtime(&fecha);
	strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",time1);
	fprintf (stderr, "*****************************************\n");
	fprintf (stderr, "\tNuevo Mensaje Leído \n");
    fprintf (stderr,"\tIdentificador: %i\n", process);
    fprintf (stderr, "\tLlave: %i\n",llave);
    fprintf (stderr, "\tFecha y Hora de creacion: %s\n",buffer);
    fprintf (stderr, "\tTotal mensajes acumulados: %i\n",total_mensajes);
    fprintf (stderr, "\tCantidad de productores: %i\n",cantidad_productores);
    fprintf (stderr, "\tCantidad de consumidores: %i\n",cantidad_consumidores);
   	fprintf (stderr, "\tAcumulado Tiempo Bloqueado: %f\n",tiempo_total_bloqueo);
    fprintf (stderr, "\tAcumulado Tiempo Bloqueado: %f\n",tiempo_total_espera);
	fprintf (stderr, "*****************************************\n");
}


//Valida si llave del mensaje leído es igual al PID del consumidor%5
int Valida_PID(int llave, int proceso)
{
	int num=proceso%5;
	if(num==llave){
		fprintf(stderr, "Consumidor con llave %i, PID: %i, Modulo:  %i \n" , llave, proceso, num);
		key_exit=ON;
		return OFF;
	}
	else{
		return ON;
	}
}

void Imprime_Stats(int proceso){
  	fprintf (stderr, "*******/******************/**********************/**************\n");
    fprintf (stderr, "   Fin de Ejecución Consumidor    \n\n");
    if (key_exit==ON){
		fprintf (stderr, "Success: Llave igual a condición de salida\n");
    }
    else {
        fprintf (stderr, "Ejecutando programa finalizador\n");
    }
                fprintf (stderr, "Identificador Consumidor: %i  \n",proceso);
                fprintf (stderr, "Total mensajes consumidos: %i\n",total_mensajes);
                fprintf (stderr, "Tiempo acumulado de espera: %f segundos\n",tiempo_total_espera);
                fprintf (stderr, "Tiempo acumulado de bloqueo : %f segundos\n",tiempo_total_bloqueo);    
    fprintf (stderr, "*******/******************/**********************/**************\n");                        
}


int Genera_Posicion(int posicion,int tamano_max){
	if (posicion < (tamano_max-1)){
		return posicion+1;
	}
	else{
		return 0;
	}
}
