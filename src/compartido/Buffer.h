#include "Mensaje.h"

#ifndef Buffer_h
#define Buffer_h

typedef struct buffer_t
{
   mensaje_t mensajes[1];
} buffer_t;

void test();

#endif