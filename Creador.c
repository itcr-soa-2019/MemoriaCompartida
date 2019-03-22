#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <Creador.h>




int main(int argc, char **argv) {
	

	if ( Crea_Buffer(argv[1],argv[2])==ERROR){
		perror("Error en la memoria compartida");
		exit(1);
	}
}

//Crea el espacio de memoria compartida por todos los procesos
int  Crea_Buffer(const char *buffer_name, char *entrada_tamano){
	
}

//Creador que inicializa todas las variablesde control 
void Inicia_Variables(){
	// incluir buffer struct 
	// Finaliza_Creador();

}

void Finaliza_Creador(){
	munmap(buf,tamano_buffer);
	fprintf (stderr, "Creador finalizado\n");
}

