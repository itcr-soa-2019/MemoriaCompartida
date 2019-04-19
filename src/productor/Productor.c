#include "Productor.h"

int main (int argc, char *argv[]) 
{
    // leer y validar parámetros
    validarParamsProductor(argc, argv);
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
    srand(time(NULL));
    while(1){
        clock_t start = clock();        
        clock_t diff;

        sem_wait(semaforoVacio);
        diff = clock() - start;
        tiempoBloqueado += diff;

        if(!buffer->activo){
            sleep(2);
            break;
        }

        // escribir mensaje
        mensaje_t mensaje = crearMensaje(producerId);
        tiempoBloqueado += escribirBuffer(buffer, mensaje, semaforoOcupado);
        contadorLocalMsjs++;

        // calcular siguiente espera
        tiempoEspera = getTiempoEspera(mediaSegundos);
        tiempoEsperaTotal += tiempoEspera;

        sem_post(semaforoLleno);
        printf("\033[1;33m");        
        printf("Esperando %lf segundos...\n", tiempoEspera);
        printf("\033[0m");
        sleep((int)round(tiempoEspera));
    }

    // decrementar productores del buffer
    decrementarProductores(buffer, semaforoOcupado);

    // imprimir reporte
    reporteProductor(producerId, contadorLocalMsjs, tiempoEsperaTotal, tiempoBloqueado);
    
    return 0;
}

void reporteProductor(int producerId, int contadorLocalMsjs, double tiempoEsperaTotal, double tiempoBloqueado) {
    sleep(1);
    printf("\n\n***********************************\n");
    colorAzul();
    printf("Resumen del Productor #%d\n", producerId);
    resetColor();
    printf("Mensajes Producidos: %d\n", contadorLocalMsjs);
    printf("Tiempo Espera Total: %lf\n", tiempoEsperaTotal);
    printf("Tiempo Bloqueado: %lf\n", tiempoBloqueado/CLOCKS_PER_SEC);    
    colorVerde();
    printf("Productor completado!!\n\n");
    resetColor();
}