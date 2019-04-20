#include "Finalizador.h"

int productores = 0;
int consumidores = 0;
int consumidoresExp = 0;
int mensajesProducidos = 0;
int mensajesConsumidos = 0;
double esperaProductores = 0;
double esperaConsumidores = 0;

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
    desactivarBufferCompartido(buffer, nombreBuffer);
    acumularDatosReporte(buffer);
    cancelarProductores(buffer, semaforoOcupado, semaforoLleno, semaforoVacio);
    cancelarConsumidores(buffer, semaforoOcupado);          
    liberarBuffer(buffer,semaforoOcupado,semaforoLleno,semaforoVacio,archivo,map_size);
    reporteFinalizador();

    return 0;
}

/**
 * Desactiva el buffer para que no puedan escribirse
 * mensajes por el productor ni leer mensajes por 
 * el consumidor.
 */
void desactivarBufferCompartido(buffer_t* buffer, char* nombre){
    printf("\n\033[1;33mTAREA [Desactivar '%s'] *****************\033[0m\n", nombre);    
    desactivarBuffer(buffer, nombre);
	puts("\033[1;32mOK: Buffer desactivado\033[0m \n");
    sleep(1);
} 

/**
 * Acumula datos para mostrarlos en el reporte final, 
 * variables globales para mantenerlas despues de 
 * desactivar y eliminar  el buffer.
 */
void acumularDatosReporte(buffer_t* buffer){
    productores = buffer->contProductores;
    consumidores = buffer->contConsumidores;
    consumidoresExp = buffer->contConsumidoresExp;
    mensajesProducidos = buffer->contTotalMensajes;
    mensajesConsumidos = buffer->contMensajesLeidos;
    esperaProductores = buffer->esperaProductores;
    esperaConsumidores = buffer->esperaConsumidores;
}

/**
 * Cancela todos los productores
 */
void cancelarProductores(buffer_t* buffer, sem_t* semaforoOcupado, sem_t* semaforoLleno, sem_t* semaforoVacio){
    puts("\n\033[1;33mTAREA [Cancelar Productores] ***************\033[0m");
    int i;
    for(i=0; i<buffer->tamano; i++)
    {
		sem_post(semaforoLleno);
		sem_post(semaforoVacio);
	}
	do {        
		sem_post(semaforoOcupado);
		sleep(2);
		sem_wait(semaforoOcupado);
    } while (getCantProductores(buffer) > 0);	
    puts("\033[1;32mOK: Productores detenidos\033[0m \n");
    sleep(1);
}

/**
 * Cancela todos los consumidores
 */
void cancelarConsumidores(buffer_t *buffer, sem_t *semaforoOcupado){
    puts("\n\033[1;33mTAREA [Cancelar Consumidores] **************\033[0m");  
	do {
		sem_post(semaforoOcupado);
		sleep(2);
		sem_wait(semaforoOcupado);
	} while (getCantConsumidores(buffer) > 0);
	puts("\033[1;32mOK: Consumidores detenidos\033[0m \n"); 
    sleep(1);
}

/**
 * Libera el buffer y los semaforos
 */ 
void liberarBuffer(buffer_t *buffer, sem_t *semaforoOcupado, sem_t *semaforoLleno, sem_t *semaforoVacio, int archivo, size_t map_size){
    puts("\n\033[1;33mTAREA [Liberar Buffer] ********************\033[0m");
    sleep(2);
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
    puts("\033[1;32mOK: Buffer liberado \033[0m\n");
    sleep(1);
}

/**
 * Imprime el reporte del finalizador
 */
void reporteFinalizador() {
    printf("\n********************************************");
    colorAzul();
    printf("\nResumen del Finalizador\n");
    resetColor();    
    printf("Productores finalizados: %d\n", productores);        
    printf("Consumidores finalizados: %d\n", consumidores);
    printf("Consumidores finalizados solos: %d\n", consumidoresExp);
    printf("Mensajes Producidos: %d\n", mensajesProducidos);
    printf("Mensajes Consumidos: %d\n", mensajesConsumidos);
    colorAzul();
    printf("Esperas (tiempo)\n");
    resetColor();
    printf("Productores: %lf segs\n", esperaProductores);    
    printf("Consumidores: %lf segs\n", esperaConsumidores);
    printf("Promedio Productores: %lf segs\n", esperaProductores/productores);    
    printf("Promedio Consumidores: %lf segs\n", esperaConsumidores/(consumidores+consumidoresExp));
    colorVerde();
    printf("Finalizador completado!!\n\n");
    resetColor();

    productores = 0, consumidores = 0, consumidoresExp = 0;
    mensajesProducidos = 0, mensajesConsumidos = 0;
    esperaProductores = 0, esperaConsumidores = 0;
}