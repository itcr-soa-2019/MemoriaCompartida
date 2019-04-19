#include "Mensaje.h"

mensaje_t crearMensaje(int pid) {
    mensaje_t mensaje;
    mensaje.pid = pid;
    mensaje.llave = rand() % 5;
    mensaje.leido = 0;
    time(&mensaje.timestampCreacion);
    
    return mensaje;
}

void imprimirMensaje(mensaje_t mensaje) {
    printf("\n----------- MENSAJE ----------\n");
    printf("Llave: %d\n", mensaje.llave);
    printf("Proceso: %d\n", mensaje.pid);
    printf("Timestamp: %s", ctime (&mensaje.timestampCreacion));
    printf("------------------------------\n");
}
