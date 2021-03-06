#include "Buffer.h"

/**
 * Inicializa estructura del buffer compartido.
 */
buffer_t* inicializarBuffer(buffer_t* buffer, char* nombre, size_t tamano, int maxMensajes) {
    buffer->nombre = nombre;
    buffer->tamano = tamano;
    buffer->maxMensajes = maxMensajes;
    buffer->activo = 1;
    buffer->contTotalMensajes = 0;
    buffer->contMensajesLeidos = 0;
    buffer->contProductores = 0;
    buffer->contConsumidores = 0;
	buffer->contConsumidoresExp = 0;
	buffer->indiceLecturaActual = 0;
   	buffer->esperaProductores = 0;
   	buffer->esperaConsumidores = 0;

    // inicializar array de mensajes aqui
	for(int i = 0; i < maxMensajes; i++){
		buffer->mensajes[i].leido = 1;
	}

    // sincronizar
    msync(buffer, buffer->tamano, MS_SYNC);
}

/**
 * Devuelve la región compartida.
 */
buffer_t* getBuffer(char* nombre) {
    int descriptorArchivo = open(nombre, O_RDWR, (mode_t)0600);
	if (descriptorArchivo == -1) {
		printf("Error obteniendo buffer compartido\n");
        exit(1);
	}
	
	off_t offset = lseek(descriptorArchivo, (size_t)0, SEEK_END);
	if (offset == -1) {
		close(descriptorArchivo);
		printf("Error obteniendo buffer compartido\n");
        exit(1);
	}
	
	size_t tamanoMapping = (size_t) (offset + 1);
	buffer_t* buffer = (buffer_t*) mmap(NULL, tamanoMapping, PROT_EXEC | PROT_READ | PROT_WRITE, 
    					MAP_SHARED, descriptorArchivo, 0);
	if (buffer == MAP_FAILED) {
		close(descriptorArchivo);
		printf("Error obteniendo buffer compartido\n");
        exit(1);
	}
    return buffer;
}

/**
 * Carga el buffer con mmap y realiza el cast
 */
buffer_t* cargarBuffer(int archivo, size_t mapSize) {
	buffer_t* buffer = (buffer_t*) mmap(NULL, mapSize, 
						PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, archivo, 0);	
	return buffer;
}

/**
 * Escribe un mensaje en el buffer.
 */
double escribirBuffer(buffer_t* buffer, mensaje_t mensaje, sem_t* semaforo) {
    clock_t inicio = clock(); 
    clock_t diff;
	
	sem_wait(semaforo);	
	msync(buffer, buffer->tamano, MS_SYNC);

	diff = clock() - inicio;
	int successfulMessage = 0;
	int index=buffer->contTotalMensajes % buffer->maxMensajes;	
	
	if(buffer->mensajes[index].leido == 1){
		buffer->mensajes[index] = mensaje;
		mensaje.tiempoBloqueado = diff;
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
 * Sincroniza el buffer
 */ 
void detenerConsumidor(buffer_t* buffer, int idConsumidor){
	msync(buffer, buffer->tamano, MS_SYNC);
	buffer->mensajes[buffer->indiceLecturaFinal].llave = idConsumidor % 5;
	buffer->mensajes[buffer->indiceLecturaFinal].mensajeFinalizacion = 1;
	buffer->indiceLecturaFinal++;
	buffer->indiceLecturaActual--;
	msync(buffer, buffer->tamano, MS_SYNC);
}

/**
 * Lee un mensaje del buffer.
 */
mensaje_t getMensaje(buffer_t* buffer, sem_t* semaforo){
	mensaje_t mensaje;
	clock_t inicio = clock(), diferencia;
	
    sem_wait(semaforo); //lock RC
	msync(buffer, buffer->tamano, MS_SYNC); //sync

	diferencia = clock() - inicio;
	mensaje.llave = -1;
	mensaje.tiempoBloqueado = diferencia;	
	int indexRead = buffer->contMensajesLeidos % buffer->maxMensajes;
	if(buffer->contMensajesLeidos < buffer->contTotalMensajes){
		mensaje = buffer->mensajes[indexRead];
		mensaje.tiempoBloqueado = diferencia;
		buffer->mensajes[indexRead].leido = 1;
		buffer->contMensajesLeidos++;
	}

	msync(buffer, buffer->tamano, MS_SYNC); //sync
    sem_post(semaforo); //unlock RC
	
    if(mensaje.llave != -1) {
		imprimirMensaje(mensaje);	
	} else {
		printf("No se pudo leer el mensaje\n");
	}
    return mensaje;
}

/**
 * Incrementa el numero de productores activos en el buffer
 * y devuelve el nuevo valor de contador para productores. 
 */
int incrementarProductores(buffer_t* buffer, sem_t* semaforo){
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
int decrementarProductores(buffer_t* buffer, sem_t* semaforo){
	int productores;
	sem_wait(semaforo);
	buffer->contProductores--;
	productores = buffer->contProductores;
	sem_post(semaforo);
	return productores;
}

/**
 * Incrementa el numero de consumidores activos en el buffer
 * y devuelve el nuevo valor de contador para consumidores. 
 */
int incrementarConsumidores(buffer_t* buffer, sem_t* semaforo){
	int consumidores;
	sem_wait(semaforo);
	buffer->contConsumidores++;
	consumidores = buffer->contConsumidores;
	sem_post(semaforo);
	return consumidores;
}

/**
 * Decrementa el numero de consumidores activos en el buffer
 * y devuelve el nuevo valor de contador para consumidores. 
 */
int decrementarConsumidores(buffer_t* buffer, sem_t* semaforo){
	int consumidores;
	sem_wait(semaforo);
	buffer->contConsumidores--;
	consumidores = buffer->contConsumidores;
	sem_post(semaforo);
	return consumidores;
}

int incrementarConsumidoresExp(buffer_t* buffer, sem_t* semaforo){
	int consumidores;
	sem_wait(semaforo);
	buffer->contConsumidoresExp++;
	consumidores = buffer->contConsumidoresExp;
	sem_post(semaforo);
	return consumidores;
}

/**
 * setea el buffer como inactivo = 0 para iniciar con la 
 * cancelacion de productores y consumidores
 */
void desactivarBuffer(buffer_t* buffer, char* nombre){	
	buffer->activo = 0;
	msync(buffer, buffer->tamano, MS_SYNC);    
}

/**
 * obtiene la cantidad de productores escribiendo mensajes
 * en el buffer compartido 
 */
int getCantProductores(buffer_t* buffer){
	msync(buffer, buffer->tamano, MS_SYNC);
	return buffer->contProductores;
}

/**
 * obtiene la cantidad de consumidores consumiendo mensajes
 * en el buffer compartido 
 */
int getCantConsumidores(buffer_t* buffer){
	msync(buffer, buffer->tamano, MS_SYNC);
	return buffer->contConsumidores;
}

/**
 * Devuelve el tiempo de espera en segundos según una
 * distribución exponencial.
 */
double getTiempoEspera (int segundos) {
    int val = rand();
    while (val == RAND_MAX)
        val = rand();
    double decimal = (double) val / RAND_MAX;
    return log (1 - decimal) * (-segundos);
}

/**
 * Incrementa el tiempo de espera acumulado de los 
 * productores para posterior uso en el reporte del finalizador
 */
double aumentarEsperaProductores(buffer_t* buffer, sem_t* semaforo, double segundos){
	sem_wait(semaforo);
	buffer->esperaProductores += segundos;
    sem_post(semaforo);	
}

/**
 * Incrementa el tiempo de espera acumulado de los 
 * consumidores para posterior uso en el reporte del finalizador
 */ 
double aumentarEsperaConsumidores(buffer_t* buffer, sem_t* semaforo, double segundos){
	sem_wait(semaforo);
	buffer->esperaConsumidores += segundos;
    sem_post(semaforo);	
}
