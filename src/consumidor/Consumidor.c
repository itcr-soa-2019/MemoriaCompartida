#include <math.h>
#include "Consumidor.h"

int main (int argc, char *argv[]) 
{
    // validar parámetros
    validarParamsConsumidor(argc, argv);

    char* nombreBuffer = argv[1];
    int mediaSegundos = strtod(argv[2], NULL);
    int mensajesConsumidos = 0;
    double tiempoEsperaTotal = 0;
    double tiempoBloqueado = 0;
    double tiempoEspera = 0;
        
    // obtener buffer compartido y semaforos
    buffer_t* buffer = getBuffer(nombreBuffer);
    sem_t *semaforoOcupado = getSemaforo(nombreSemaforoOcupado);
    sem_t *semaforoVacio = getSemaforo(nombreSemaforoVacio);
    sem_t *semaforoLleno = getSemaforo(nombreSemaforoLleno);

    // incrementar consumidores del buffer
    int idConsumidor = incrementarConsumidores(buffer, semaforoOcupado);

    // leer mensajes
    while(1)
    {
        clock_t inicio = clock();
        clock_t diff;

        sem_wait(semaforoLleno); //lock
        diff = clock() - inicio;        
        tiempoBloqueado += diff;

        if(!buffer->activo){
            sleep(2);
            break;
        }

        mensaje_t mensaje = getMensaje(buffer, semaforoOcupado);
        if (mensaje.llave != -1) {
            mensajesConsumidos++;
        }
        if (idConsumidor % 5 == mensaje.llave) {
            colorAmarillo();
            printf("Se cumple condición de finalización\n");
            resetColor();
            incrementarConsumidoresExp(buffer, semaforoOcupado);
            sem_post(semaforoVacio); // unlock
            break;
        }

        // calcular siguiente espera
        tiempoBloqueado += mensaje.tiempoBloqueado;
        tiempoEspera = getTiempoEspera(mediaSegundos);
        tiempoEsperaTotal += tiempoEspera;
        aumentarEsperaConsumidores(buffer, semaforoOcupado, tiempoEspera);
        
        sem_post(semaforoVacio); // unlock
        colorAmarillo();
        printf("Esperando %lf segundos...\n", tiempoEspera);
        resetColor();
        sleep((int)round(tiempoEspera));
    }

    // decrementar consumidores del buffer
    decrementarConsumidores(buffer, semaforoOcupado);

    // imprimir reporte
    reporteConsumidor(idConsumidor,mensajesConsumidos,tiempoEsperaTotal,tiempoBloqueado);
    
    return 0;
}

/**
 * Imprime el reporte del consumidor
 */
void reporteConsumidor(int idConsumidor, int mensajesConsumidos, double tiempoEsperaTotal, double tiempoBloqueado) {
    sleep(1);
    printf("\n\n***********************************\n");
    colorAzul();
    printf("Resumen del Consumidor #%d\n", idConsumidor);
    resetColor();
    printf("Mensajes Consumidos: %d\n", mensajesConsumidos);
    printf("Tiempo Espera Total: %lf\n", tiempoEsperaTotal);
    printf("Tiempo Bloqueado: %lf\n", tiempoBloqueado/CLOCKS_PER_SEC);    
    colorVerde();
    printf("Consumidor completado!!\n\n");
    resetColor();
}