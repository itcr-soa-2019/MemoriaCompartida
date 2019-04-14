#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "Buffer.c"
#include "DistExponencial.c"
#include "Generalidades.c"
//#include "Creador.h"

int Inicia_MemoriaCompartida(const char *nombre_buffer, char *segundos);
void Inicializa_Consumidor();
void Asigna_Consumidor(int pid);
void Finaliza_Consumidor(int pid);
void Crea_Mensaje(int process);
int  Valida_PID(int key, int process);
void Despliega_Mensaje(int process, int key, time_t fecha, int posicion, int cantidad_prod, int cantidad_cons);
void Imprime_Stats(int process);
int Genera_Posicion(int posicion,int tamano_max);
