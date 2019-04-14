
#include <stdio.h>
#include <stdlib.h>
#include "Mensaje.h"
#include <semaphore.h>

struct buffer {
    char* nombre_buffer;
    int tamano_buffer;
    int contador_productores;
    int contador_consumidores;
    int actual_lectura;
    int actual_escritura;
    unsigned int mensajes_totales;
    unsigned int consumidores_totales;
    int flag_exec;
    struct list_mensajes buffer_list[1];
    sem_t sem0,sem1,sem2;   //semaphore operation
};


int Existe_Buffer(char *nombre_buffer);
 