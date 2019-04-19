#include <stdio.h>
#include <stdlib.h>
#include "../compartido/Buffer.h"
#include "../compartido/Mensaje.h"
#include "../compartido/Semaforo.h"
#include "../compartido/Validador.h"

#ifndef Finalizador_h
#define Finalizador_h

void cancelarProductores(buffer_t* buffer, sem_t* semaforoOcupado, sem_t* semaforoLleno, sem_t* semaforoVacio, int tamano);
void cancelarConsumidores(buffer_t *buffer, sem_t *semaforoOcupado);
void eliminarBuffer(buffer_t *buffer, sem_t *semaforoOcupado, sem_t *semaforoLleno, sem_t *semaforoVacio, int archivo, size_t map_size);
void reporteFinalizador();

#endif