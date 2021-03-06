#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "Mensaje.h"

#ifndef Buffer_h
#define Buffer_h

typedef struct buffer_t
{
   char* nombre;
   size_t tamano;
   int activo;
   int maxMensajes;
   int contTotalMensajes;
   int contMensajesLeidos;
   int contProductores;
   int contConsumidores;
   int contConsumidoresExp;
   double esperaProductores;
   double esperaConsumidores;
   int indiceLecturaActual;
   int indiceLecturaInicial;
   int indiceLecturaFinal;
   mensaje_t mensajes[];
} buffer_t;


buffer_t* inicializarBuffer(buffer_t* buffer, char* nombre, size_t tamano, int maxMensajes);
buffer_t* getBuffer(char* nombre);
buffer_t* cargarBuffer(int archivo, size_t mapSize);
double escribirBuffer(buffer_t* buffer, mensaje_t mensaje, sem_t* semaforo);
void detenerConsumidor(buffer_t* buffer, int idConsumidor);
mensaje_t getMensaje(buffer_t* buffer, sem_t* semaforo);
int incrementarProductores(buffer_t* buffer, sem_t* semaforo);
int decrementarProductores(buffer_t* buffer, sem_t* semaforo);
int incrementarConsumidores(buffer_t* buffer, sem_t* semaforo);
int decrementarConsumidores(buffer_t* buffer, sem_t* semaforo);
int incrementarConsumidoresExp(buffer_t* buffer, sem_t* semaforo);
void desactivarBuffer(buffer_t* buffer, char* nombre);
int getCantProductores(buffer_t* buffer);
int getCantConsumidores(buffer_t* buffer);
double getTiempoEspera (int segundos);
double aumentarEsperaProductores(buffer_t* buffer, sem_t* semaforo, double segundos);
double aumentarEsperaConsumidores(buffer_t* buffer, sem_t* semaforo, double segundos);

#endif