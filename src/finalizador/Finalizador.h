#include <stdio.h>
#include <stdlib.h>
#include "../compartido/Buffer.h"
#include "../compartido/Mensaje.h"
#include "../compartido/Semaforo.h"

#ifndef Finalizador_h
#define Finalizador_h

void validarParamsFinalizador(int contArgs);
void reporteFinalizador(buffer_t *buffer);
void desactivarBuffer();
void cancelarProductores();
void cancelarConsumidores();

#endif