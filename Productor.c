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

	//tamano_buffer=1;
	buf = mmap(NULL, (sizeof(struct buffer)+sizeof(struct list_mensajes)*tamano_buffer),
	       PROT_READ | PROT_WRITE, MAP_SHARED, smo, 0);
	if (buf == MAP_FAILED){
		return ERROR;
	}
	Inicializa_Productor(atof(segundos));
	return 1;
}

void Inicializa_Productor(double segundos){
	//fprintf (stderr, "Nuevo Productor Inicializado\n");
	
}

//Registra un nuevo productor en la memoria compartida
void Asigna_Productor(){
	
}


//Libera memoria y despliega
void Finaliza_Productor(){
	
	//Despligue_Total();
}

//Crea un nuevo mensaje en el buffer
void Crea_Mensaje(){
	
	//Despliega_Mensaje();
}


void Despliega_Mensaje(){
	
    fprintf (stderr, "\tNuevo Mensaje en el buffer \n");
    fprintf (stderr,"\tIdentificacion del productor: \n");
    fprintf (stderr, "\tFecha y Hora de creacion:\n");
    fprintf (stderr, "\tLlave: \n");

}

void Despligue_Total(){
     fprintf (stderr, "*****************************************\n");
     fprintf (stderr, "   Fin de Ejecución Productor    \n\n");
     fprintf (stderr, "*****************************************\n");
}



