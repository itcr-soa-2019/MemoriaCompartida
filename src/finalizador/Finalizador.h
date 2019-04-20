#include <stdio.h>
#include <stdlib.h>
#include "../compartido/Buffer.h"
#include "../compartido/Mensaje.h"
#include "../compartido/Semaforo.h"
#include "../compartido/Validador.h"

#ifndef Finalizador_h
#define Finalizador_h

void desactivarBufferCompartido(buffer_t* buffer, char* nombre);
void acumularDatosReporte(buffer_t* buffer);
void cancelarProductores(buffer_t* buffer, sem_t* semaforoOcupado, sem_t* semaforoLleno, sem_t* semaforoVacio);
void cancelarConsumidores(buffer_t *buffer, sem_t *semaforoOcupado);
void liberarBuffer(buffer_t *buffer, sem_t *semaforoOcupado, sem_t *semaforoLleno, sem_t *semaforoVacio, int archivo, size_t map_size);
void reporteFinalizador();

#endif