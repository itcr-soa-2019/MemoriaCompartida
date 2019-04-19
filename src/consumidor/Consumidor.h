#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "../compartido/Buffer.h"
#include "../compartido/Mensaje.h"
#include "../compartido/Semaforo.h"
#include "../compartido/Validador.h"

#ifndef Consumidor_h
#define Consumidor_h

void reporteConsumidor(int idConsumidor, int mensajesConsumidos, double tiempoEsperaTotal, double tiempoBloqueado);

#endif