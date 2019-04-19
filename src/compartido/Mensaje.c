#include "Mensaje.h"

mensaje_t crearMensaje(int pid) {
    mensaje_t mensaje;
    mensaje.pid = pid;
    mensaje.llave = rand() % 5;
    mensaje.leido = 0;
    mensaje.tiempoBloqueado = 0;
    mensaje.mensajeFinalizacion = 0;    
    time(&mensaje.timestampCreacion);
    
    return mensaje;
}

void imprimirMensaje(mensaje_t mensaje) {
    printf("\n-------------- MENSAJE ------------\n");
    printf("Llave: %d\n", mensaje.llave);
    printf("Proceso: %d\n", mensaje.pid);
    printf("Timestamp: %s", ctime (&mensaje.timestampCreacion));
    printf("-----------------------------------\n\n");
}

void colorAzul() {
    printf("\033[1;34m");
}

void colorAmarillo() {
    printf("\033[1;33m");
}

void colorVerde() {
    printf("\033[1;32m");
}

void colorRojo() {
    printf("\033[1;31m");
}

void resetColor() {
    printf("\033[0m");
}
