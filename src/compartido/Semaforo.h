#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "Mensaje.h"

#ifndef Semaforo_h
#define Semaforo_h

char *nombreSemaforoOcupado = "/semOcupado";
char *nombreSemaforoVacio = "/semVacio";
char *nombreSemaforoLleno = "/semLleno";

sem_t* crearSemaforo(char* nombre, int valor);
sem_t* getSemaforo(char* nombre);

#endif