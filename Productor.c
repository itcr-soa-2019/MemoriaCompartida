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
	// obtener parametros
	// Inicia_MemoriaCompartida()
	
}

int Inicia_MemoriaCompartida (const char *nombre_buffer, char *segundos) {
	
}

void Inicializa_Productor(){
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



