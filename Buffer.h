
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
    struct buffer *next;
};

/**
 * Este struct va a utilizarse unicamente
 * para validar los nombres de buffers y saber
 * si ya han sido previamente registrados.
 */
struct buffer_list
{
   struct buffer *head;
   struct buffer *last;
};

struct buffer_list buffer_list;
 

int Agregar_Buffer(struct buffer *buffer);
void Borrar_Buffers(struct buffer *buffer);
int Existe_Buffer(char *nombre_buffer);
 