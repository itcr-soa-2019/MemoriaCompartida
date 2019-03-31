#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "Productor.h"


int main(int argc, char **argv)
{
	int parameters;
	parameters=Validar_Parametros(argc, argv, "Nombre Productor","Segundos");
    // falta validar si ya existe el buffer sino hay que crearlo!!!
	if ( Inicia_MemoriaCompartida(argv[1],argv[2])==ERROR){
		perror("Error en la memoria compartida");
		exit(1);
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
	int estado;
	int exec =1;
	float tiempo_espera;
	int a;
	double tiempo_consumido;
	pid_t proceso_productor;
	time_t inicio, final;

	proceso_productor = getpid(); //returns the process ID (PID) of the calling process (used by routines that generate unique temporary filenames.)
	Asigna_Productor(proceso_productor);
	fprintf (stderr, "Nuevo productor iniciado %i \n",proceso_productor);
	
		while (exec){
			tiempo_espera=Exponential(segundos);
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

//Crea un nuevo mensaje en el buffer
void Crea_Mensaje(int pid){
	
	//Despliega_Mensaje();
}


//Libera memoria y despliega
void Finaliza_Productor(int pid){
	buf->contador_productores=buf->contador_productores-1;
	munmap(buf,tamano_buffer);
	close(smo);
	Despligue_Total(pid);
	
}



void Despliega_Mensaje(){
	
    fprintf (stderr, "\tNuevo Mensaje en el buffer \n");
    fprintf (stderr,"\tIdentificacion del productor: \n");
    fprintf (stderr, "\tFecha y Hora de creacion:\n");
    fprintf (stderr, "\tLlave: \n");

}

void Despligue_Total(int pid){
     fprintf (stderr, "*****************************************\n");
     fprintf (stderr, "   Fin de Ejecución Productor    \n\n");
     fprintf (stderr, "*****************************************\n");
}



