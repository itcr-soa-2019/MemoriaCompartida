#include "Buffer.h"

buffer_t* inicializarBuffer(buffer_t* buffer, char* nombre, size_t tamano, int maxMensajes) {
    buffer->nombre = nombre;
    buffer->tamano = tamano;
    buffer->maxMensajes = maxMensajes;
    buffer->activo = 1;
    buffer->contTotalMensajes = 0;
    buffer->contMensajesLeidos = 0;
    buffer->contProductores = 0;
    buffer->contConsumidores = 0;

    // inicializar array de mensajes aqui
	for(int i = 0; i < maxMensajes; i++){
		buffer->mensajes[i].leido = 1;
	}

    // sincronizar
    msync(buffer, buffer->tamano, MS_SYNC);
}

buffer_t* getBuffer(char* nombre) {
    int descriptorArchivo = open(nombre, O_RDWR, (mode_t)0600);
	if (descriptorArchivo == -1) {
		printf("1Error obteniendo buffer compartido\n");
        exit(1);
	}
	
	off_t offset = lseek(descriptorArchivo, (size_t)0, SEEK_END);
	if (offset == -1) {
		close(descriptorArchivo);
		printf("2Error obteniendo buffer compartido\n");
        exit(1);
	}
	
	size_t tamanoMapping = (size_t) (offset + 1);
	buffer_t* buffer = (buffer_t*) mmap(NULL, tamanoMapping, PROT_EXEC | PROT_READ | PROT_WRITE, 
    MAP_SHARED, descriptorArchivo, 0);
	if (buffer == MAP_FAILED) {
		close(descriptorArchivo);
		printf("3Error obteniendo buffer compartido\n");
        exit(1);
	}
    return buffer;
}

double escribirBuffer(buffer_t* buffer, mensaje_t mensaje, sem_t* semaforo) {
    clock_t inicio = clock(); 
    clock_t diff;
	sem_wait(semaforo);
	diff = clock() - inicio;
	msync(buffer, buffer->tamano, MS_SYNC);
	int index;
	int successfulMessage = 0;
	
	index = buffer->contTotalMensajes % buffer->maxMensajes;
	
	if(buffer->mensajes[index].leido == 1){
		buffer->mensajes[index] = mensaje;
		buffer->contTotalMensajes++;
		successfulMessage = 1;
	}
	
	msync(buffer, buffer->tamano, MS_SYNC);
	
	sem_post(semaforo);
	if(successfulMessage) {
        imprimirMensaje(mensaje);
    }
    return diff;
}

/**
 * Incrementa el numero de productores activos en el buffer
 * y devuelve el nuevo valor de contador para productores. 
 */
int incrementarContProductores(buffer_t* buffer, sem_t* semaforo){
	int productores;
	sem_wait(semaforo);
	buffer->contProductores++;
	productores = buffer->contProductores;
	sem_post(semaforo);
	return productores;
}

/**
 * Decrementa el numero de productores activos en el buffer
 * y devuelve el nuevo valor de contador para productores. 
 */
int decrementarContProductores(buffer_t* buffer, sem_t* semaforo){
	int productores;
	sem_wait(semaforo);
	buffer->contProductores--;
	productores = buffer->contProductores;
	sem_post(semaforo);
	return productores;
}