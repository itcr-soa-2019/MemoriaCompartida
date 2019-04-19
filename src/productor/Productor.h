#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../compartido/Buffer.h"
#include "../compartido/Mensaje.h"
#include "../compartido/Semaforo.h"
#include "../compartido/Validador.h"

#ifndef Productor_h
#define Productor_h

void reporteProductor(int producerId, int contadorLocalMsjs, double tiempoEsperaTotal, double tiempoBloqueado);

#endif