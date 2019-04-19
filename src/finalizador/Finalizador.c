#include "Finalizador.h"

int productores = 0;
int consumidores = 0;
int mensajesProducidos = 0;
int mensajesConsumidos = 0;

int main (int argc, char *argv[]) 
{
    validarParamsFinalizador(argc);
    char* nombreBuffer = argv[1];

    int archivo = open(nombreBuffer, O_RDWR, (mode_t)0600);
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

    buffer_t* buffer = cargarBuffer(archivo, map_size);
    sem_t* semaforoOcupado = getSemaforo(nombreSemaforoOcupado);
    sem_t* semaforoVacio = getSemaforo(nombreSemaforoVacio);
    sem_t* semaforoLleno = getSemaforo(nombreSemaforoLleno);

	sem_wait(semaforoOcupado);    
    desactivarBuffer(buffer, nombreBuffer);

    productores = buffer->contProductores;
    consumidores = buffer->contConsumidores;
    mensajesProducidos = buffer->contTotalMensajes;
    mensajesConsumidos = buffer->contMensajesLeidos;

    cancelarProductores(buffer, semaforoOcupado, semaforoLleno, semaforoVacio, buffer->tamano);
    cancelarConsumidores(buffer, semaforoOcupado);          
    eliminarBuffer(buffer,semaforoOcupado,semaforoLleno,semaforoVacio,archivo,map_size);
    reporteFinalizador();

    return 0;
}

/**
 * Cancela todos los productores
 */
void cancelarProductores(buffer_t* buffer, sem_t* semaforoOcupado, sem_t* semaforoLleno, sem_t* semaforoVacio, int tamano){
    printf("\n-----------------------------------------\n");
    puts("\nCancelando los productores...");
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
    puts("Todos los productores han sido detenidos");
    printf("\n-----------------------------------------\n");
}

/**
 * Cancela todos los consumidores
 */
void cancelarConsumidores(buffer_t *buffer, sem_t *semaforoOcupado){
    puts("\nCancelando los consumidores...");
    int consumidor = getCantConsumidores(buffer);
	for (; consumidor > 0; consumidor--) {
		printf("Deteniendo consumidor %d...\n", consumidor);
        sleep(2);
        detenerConsumidor(buffer, consumidor);
	}
	do {
		sem_post(semaforoOcupado);
		sleep(2);
		sem_wait(semaforoOcupado);
	} while (getCantConsumidores(buffer) > 0);
	puts("Todos los consumidores han sido detenidos");    
    printf("\n-----------------------------------------\n");
}

/**
 * Elimina el buffer y los semaforos
 */ 
void eliminarBuffer(buffer_t *buffer, sem_t *semaforoOcupado, sem_t *semaforoLleno, sem_t *semaforoVacio, int archivo, size_t map_size){
    puts("\nEliminando el buffer...");
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
    sleep(1);
    puts("Buffer eliminado\n");
}

/**
 * Imprime el reporte del finalizador
 */
void reporteFinalizador() {
    printf("\n*****************************************");
    printf("\nResumen del Finalizador");
    printf("\n-----------------------------------------\n");
    printf("\tProductores finalizados: %d\n", productores);        
    printf("\tConsumidores finalizados: %d\n", consumidores);
    printf("\tMensajes Producidos: %d\n", mensajesProducidos);
    printf("\tMensajes Consumidos: %d\n\n", mensajesConsumidos);
    productores = 0, consumidores = 0, mensajesProducidos = 0, mensajesConsumidos = 0;
}