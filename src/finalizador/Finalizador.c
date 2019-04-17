#include "Finalizador.h"

int main (int argc, char *argv[]) 
{
    // validar los parametros
    validarParamsFinalizador(argc);
    
    char* nombreBuffer = argv[1];
    int maxMensajes = atoi(argv[2]);

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
    
    // detener los procesos
    desactivarBuffer();
    cancelarProductores();
    cancelarConsumidores();

    // reporte del finalizador
    reporteFinalizador(buffer);

    // cancelar los procesos
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

    return 0;
}

void validarParamsFinalizador(int contArgs) {
    if (contArgs != 2) {
        printf("Error en los parámetros: Ingrese el nombre del buffer.\n");
        exit(1);
    }
}

void reporteFinalizador(buffer_t *buffer) {
    printf("\n***********************\n");
    printf("Mensajes Producidos: %d\n", buffer->contTotalMensajes);
    printf("Mensajes Consumidos: %d\n", buffer->contMensajesLeidos);
    printf("Finalizador completado!!\n");
}

void desactivarBuffer(){
    // TODO
}

void cancelarProductores(){
    // TODO
}

void cancelarConsumidores(){
    // TODO
}