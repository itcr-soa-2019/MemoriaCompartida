#include <time.h>

#ifndef Mensaje_h
#define Mensaje_h

typedef struct mensaje_t
{
    time_t fechaCreacion;
    int llave;
    int pid;
    int flagExec;

} mensaje_t;

#endif