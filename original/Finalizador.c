#include "Finalizador.h"


int main(int argc, char **argv) {
	if (argc < 2) {
		indicaciones(1,"Finalizador","","Faltan parámetros de ingreso.");
	}
	else if (argc > 2) {
		indicaciones(1,"Finalizador","","Ingreso más parámetros.");
	}
	else{
		if ( Inicia_MemoriaCompartida(argv[1])==ERROR){
			perror("No se puede mapear la memoria compartida");
			exit(1);
		}
	}
	
}


int Inicia_MemoriaCompartida(const char *nombre_buffer){
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
    Inicializa_Finalizador();
	return 1;
}

void Inicializa_Finalizador(){
	int count,a;
	int proceso=getpid();
	int num_consumidores=buf->contador_consumidores;
	buf->flag_exec=OFF;
	for (count=0;count<num_consumidores;count++){
        sem_wait(&(buf->sem1));
        	sem_wait(&(buf->sem0));
        	sem_getvalue(&(buf->sem2),&a);
				Crea_Mensaje(proceso);
			sem_post(&(buf->sem0));
	    sem_post(&(buf->sem2));
	}
    Cancela_procesos();
}


void Crea_Mensaje(int proceso){
    
	time_t current_time =time(NULL);
    int posicion=buf->actual_escritura;
	buf->buffer_list[posicion].pid=proceso;
	buf->buffer_list[posicion].fecha_creacion=	current_time;
	buf->buffer_list[posicion].llave=Genera_Llave_Aleatoria();
	buf->buffer_list[posicion].flag_exec=OFF;
	buf->actual_escritura= Genera_Posicion(posicion, buf->tamano_buffer);
	buf->mensajes_totales=buf->mensajes_totales+1;

}


int Genera_Posicion(int posicion,int tamano_max){
	if (posicion < (tamano_max-1)){
		return posicion+1;
	}
	else{
		return 0;
	}
}

void Cancela_procesos(){
	while(1){
		if((buf->contador_productores==0) && (buf->contador_consumidores==0)){
			Imprime_Stats();
			int n;
			sem_post(&(buf->sem0));
			sem_post(&(buf->sem2));
			sem_post(&(buf->sem1));
			buf->flag_exec=OFF;
			munmap(buf,tamano_buffer);
			sem_destroy(&(buf->sem2));
			sem_destroy(&(buf->sem0));
			sem_destroy(&(buf->sem1));
			close(smo);
			break;
		}
		else{
			sleep(1);
		}
	}


}

void Imprime_Stats(){
    fprintf (stderr, "/---------------------------------------------------------/\n");
    fprintf (stderr, "Cancelando el Sistema de Procesos... \n\n");
    fprintf (stderr, "Proceso: %i  \n",getpid());
    fprintf (stderr, "Total de consumidores activos: %i\n",buf->contador_consumidores);
    fprintf (stderr, "Total de productores: %i\n",buf->contador_productores);
    fprintf (stderr, "Tamaño del buffer: %i\n",buf->tamano_buffer);
    fprintf (stderr, "Total de consumidores durante la ejecución: %u\n",buf->consumidores_totales);
    fprintf (stderr, "Total de mensajes: %u\n",buf->mensajes_totales);
    fprintf (stderr, "/---------------------------------------------------------/\n");
}
