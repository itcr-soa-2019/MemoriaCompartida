#include <math.h>
#include "Productor.h"

/**
 * 
 * Todavia ocupa arreglos
 * 
 * */
int main (int argc, char *argv[]) 
{
    // leer y validar parámetros
    validarParamsProduct(argc);
    char* nombreBuffer = argv[1];
    int mediaSegundos = strtod(argv[2], NULL);
    int contadorLocalMsjs = 0;
    double tiempoBloqueado = 0; // tiempo que estuvo bloqueado por semáforos
    double tiempoEsperaTotal = 0; // tiempo total de espera durante la ejecución de este productor
    double tiempoEspera = 0; // espera entre un mensaje y otro

    // obtener buffer compartido
    buffer_t* buffer = getBuffer(nombreBuffer);

    // obtener semáforos
    sem_t *semaforoOcupado = getSemaforo(nombreSemaforoOcupado);
    sem_t *semaforoVacio = getSemaforo(nombreSemaforoVacio);
    sem_t *semaforoLleno = getSemaforo(nombreSemaforoLleno);
    
    // incrementar productores del buffer
    int producerId = incrementarProductores(buffer, semaforoOcupado);

    // producir mensajes
    srand(time(NULL)); //srand((unsigned) time(&t));    
    while(1){
        clock_t start = clock();
        clock_t diff;
        printf("Pegado en el semaforo\n");
        sem_wait(semaforoVacio);
        diff = clock() - start;
        printf("Productor trabajandoo...\n");
        tiempoBloqueado += diff;

        if(!buffer->activo){
            break;
        }
        mensaje_t mensaje = crearMensaje(producerId);

        // escribir mensaje
        tiempoBloqueado += escribirBuffer(buffer, mensaje, semaforoOcupado);
        contadorLocalMsjs++;

        // calcular siguiente espera
        tiempoEspera = getTiempoEspera(mediaSegundos);
        tiempoEsperaTotal += tiempoEspera;
        sem_post(semaforoLleno);
        printf("Esperando %lf segundos...\n", tiempoEspera);
        sleep((int)round(tiempoEspera));
    }

    // decrementar productores del buffer
    decrementarProductores(buffer, semaforoOcupado);

    // imprimir reporte
    reporteProductor(producerId, contadorLocalMsjs, tiempoEsperaTotal, tiempoBloqueado);
    
    return 0;
}

void validarParamsProduct(int contArgs) {
    if (contArgs != 3) {
        printf("Error en los parámetros: Ingrese el nombre del buffer y la media de espera en segundos.\n");
        exit(1);
    }
}

void reporteProductor(int producerId, int contadorLocalMsjs, double tiempoEsperaTotal, double tiempoBloqueado) {
    printf("\n***********************\n");
    printf("Resumen del Productor: %d\n", producerId);
    printf("Mensajes Producidos: %d\n", contadorLocalMsjs);
    printf("Tiempo Espera Total: %lf\n", tiempoEsperaTotal);
    printf("Tiempo Bloqueado: %lf\n", tiempoBloqueado);
    printf("Productor completado!!\n");
}