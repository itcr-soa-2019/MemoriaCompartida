#include "Mensaje.h"
#include <semaphore.h>

#ifndef Buffer_h
#define Buffer_h

typedef struct buffer_t
{
   char* nombre;
   size_t tamano;
   int activo;
   int maxMensajes;
   int contTotalMensajes;
   int contMensajesLeidos;
   int contProductores;
   int contPonsumidores;
   //int __frontIndex;
   //int __backIndex;
   mensaje_t mensajes[];
} buffer_t;

buffer_t* inicializarBuffer(buffer_t* buffer, char* nombre, size_t tamano, int maxMensajes);

#endif