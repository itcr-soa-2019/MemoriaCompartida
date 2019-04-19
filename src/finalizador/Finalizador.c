#include "Finalizador.h"

int main (int argc, char *argv[]) 
{
    // validar los parametros
    validarParamsFinalizador(argc);    

    // parametros de entrada
    char* nombreBuffer = argv[1];

    // abrir archivo con nombre de buffer
    int archivo = open(nombreBuffer, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (archivo == -1) {
        printf("Error cargando archivo compartido\n");
        exit(1);
    }
    __off_t offset = lseek(archivo, (size_t) 0, SEEK_END);
	if (offset == -1) {
		return (size_t) offset;
	}
	size_t map_size = (size_t) (offset + 1);
	if (map_size == -1) {
		close(archivo);
		return -1;
	}

    // obtener buffer compartido y semaforos
    buffer_t* buffer = getBuffer(nombreBuffer);
    sem_t *semaforoOcupado = getSemaforo(nombreSemaforoOcupado);
    sem_t *semaforoVacio = getSemaforo(nombreSemaforoVacio);
    sem_t *semaforoLleno = getSemaforo(nombreSemaforoLleno);
    
	sem_wait(semaforoOcupado); // lock del semaforo

    desactivarBufferCompartido(buffer);
    //cancelarProductores(buffer, semaforoOcupado, semaforoLleno, semaforoVacio, buffer->tamano);
    //cancelarConsumidores(buffer, semaforoOcupado);
    reporteFinalizador(buffer);    
    //eliminarBuffer(buffer,semaforoOcupado,semaforoLleno,semaforoVacio,archivo,map_size);

    return 0;
}

void validarParamsFinalizador(int contArgs) {
    if (contArgs != 2) {
        printf("Error en los parámetros: Ingrese el nombre del buffer.\n");
        exit(1);
    }
}

void desactivarBufferCompartido(buffer_t* buffer){
	printf("\nDesactivando el buffer '%s'...\n", "XXX");
    desactivarBuffer(buffer);
    sleep(2);
	printf("\nBuffer '%s' desactivado...\n", "XXX");
}

void cancelarProductores(buffer_t* buffer, sem_t* semaforoOcupado, sem_t* semaforoLleno, sem_t* semaforoVacio, int tamano){
    printf("Cancelando los productores...\n");
    int i;
    for(i=0; i<tamano; i++)
    {
		sem_post(semaforoLleno);
		sem_post(semaforoVacio);
	}
	do {
		sem_post(semaforoOcupado);
		sleep(2);
		sem_wait(semaforoOcupado);
    } while (getCantProductores(buffer) > 0);	
    puts("Todos los productores han sido detenidos...\n");
}

void cancelarConsumidores(buffer_t *buffer, sem_t *semaforoOcupado){
    printf("Cancelando los consumidores...\n");
    int consumidor = getCantConsumidores(buffer);
	for (; consumidor > 0; consumidor--) {
		printf("Deteniendo el consumidor %d...\n", consumidor);
		//shared_buffer_put_stop(buffer, consumidor);
	}
	do {
		sem_post(semaforoOcupado);
		sleep(2);
		sem_wait(semaforoOcupado);
	} while (getCantConsumidores(buffer) > 0);
	puts("Todos los consumidores han sido detenidos...\n");    
}

void eliminarBuffer(buffer_t *buffer, sem_t *semaforoOcupado, sem_t *semaforoLleno, sem_t *semaforoVacio, int archivo, size_t map_size){
    puts("Eliminando el buffer...\n");
    if (buffer != MAP_FAILED) {
		munmap(buffer, map_size);
	}
	close(archivo);	
    sem_close(semaforoOcupado);
	sem_close(semaforoLleno);
    sem_close(semaforoVacio);
    sem_unlink(nombreSemaforoOcupado);	
	sem_unlink(nombreSemaforoLleno);
	sem_unlink(nombreSemaforoVacio);
    puts("Buffer eliminado...\n");
}

void reporteFinalizador(buffer_t *buffer) {
    printf("\n***********************\n");
    printf("Cancelando el Sistema de Procesos...\n\n");
    printf("Mensajes Producidos: %d\n", buffer->contTotalMensajes);
    printf("Mensajes Consumidos: %d\n", buffer->contMensajesLeidos);
    printf("Finalizador completado!!\n");
}