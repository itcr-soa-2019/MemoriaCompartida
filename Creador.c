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
	int parameters;
	parameters=Validar_Parametros(argc, argv, "Nombre","Tamaño_Buffer");
	if ( Crea_Buffer(argv[1],argv[2])==ERROR){
		perror("Error en la memoria compartida");
		exit(1);
	}
}

//Crea el espacio de memoria compartida para todos los procesos
int  Crea_Buffer(const char *nombre_buffer, char *entrada_tamano){
	tamano_buffer = atoi(entrada_tamano);//convierte string a integer 
	// shared memory object,O_CREAT crea el objeto sino existe, O_RDWR read - write access al objeto, S_IRUSR | S_IWUSR read-write permission para el dueno del archivo
	smo = shm_open(nombre_buffer, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); 
	if (smo == -1){
		return ERROR;
	} 
	Inicia_Variables();
	return 1;
}

//Creador que inicializa todas las variables de control 
void Inicia_Variables(){
	// buffer struct 
	buf -> tamano_buffer = tamano_buffer;
    buf -> contador_productores = 0;
    buf -> contador_consumidores = 0;
    buf -> actual_lectura = 0;
    buf -> actual_escritura = 0;
    buf -> mensajes_totales = 0;
    buf -> consumidores_totales = 0;
    buf -> flag_exec = ON;

	//inicia 2 semaphores 
	/*sem_init() initializes the unnamed semaphore at the address pointed
       to by sem.  The value argument specifies the initial value for the
       semaphore.

       The pshared argument indicates whether this semaphore is to be shared
       between the threads of a process, or between processes.

       If pshared has the value 0, then the semaphore is shared between the
       threads of a process, and should be located at some address that is
       visible to all threads (e.g., a global variable, or a variable
       allocated dynamically on the heap).

       If pshared is nonzero, then the semaphore is shared between
       processes, and should be located in a region of shared memory
	   returns 0 on success; on error, -1 is returned*/

	sem_init(&buf->sem1, 1, 1);
	sem_init (&buf->sem2, 1, tamano_buffer);
	

	Finaliza_Creador();

}

void Finaliza_Creador(){
	munmap(buf,tamano_buffer); //unmap pages of memory, remove any mappings
	fprintf (stderr, "Creador finalizado\n");
}

