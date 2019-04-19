#include <stdio.h>
#include <stdlib.h>
#include "../compartido/Buffer.h"
#include "../compartido/Mensaje.h"
#include "../compartido/Semaforo.h"

#ifndef Finalizador_h
#define Finalizador_h

void validarParamsFinalizador(int contArgs);
void reporteFinalizador(buffer_t *buffer);
void eliminarBuffer(buffer_t *buffer, sem_t *semaforoOcupado, sem_t *semaforoLleno, sem_t *semaforoVacio, int archivo, size_t map_size);
void cancelarProductores(buffer_t* buffer, sem_t* semaforoOcupado, sem_t* semaforoLleno, sem_t* semaforoVacio, int tamano);
void cancelarConsumidores();

#endif