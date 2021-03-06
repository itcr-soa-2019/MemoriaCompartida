#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef Mensaje_h
#define Mensaje_h

typedef struct mensaje_t
{
    time_t timestampCreacion;
    int llave;
    int pid;
    int leido;
    double tiempoBloqueado;
    int mensajeFinalizacion;
} mensaje_t;

mensaje_t crearMensaje(int pid);
void imprimirMensaje(mensaje_t mensaje);

void colorAzul();
void colorAmarillo();
void colorVerde();
void colorRojo();
void resetColor();

#endif