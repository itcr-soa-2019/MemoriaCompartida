#include <time.h>

#ifndef Mensaje_h
#define Mensaje_h

typedef struct mensaje_t
{
    time_t timestampCreacion;
    int llave;
    int pid;
    int leido;

} mensaje_t;

mensaje_t crearMensaje(int pid);
void imprimirMensaje(mensaje_t mensaje);

#endif