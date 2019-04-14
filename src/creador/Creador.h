#include <semaphore.h>

#ifndef Creador_h
#define Creador_h

char *nombreSemaforoOcupado = "/semOcupado";
char *nombreSemaforoVacio = "/semVacio";
char *nombreSemaforoLleno = "/semLleno";

void validarParams(int contArgs, char *args[]);
sem_t* crearSemaforo(char* nombre, int valor);
sem_t* getSemaforo(char* nombre);

#endif