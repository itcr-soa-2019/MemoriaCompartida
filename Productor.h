#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <semaphore.h>
#include "Buffer.c"
#include "DistExponencial.c"
#include "Generalidades.c"


int Inicia_MemoriaCompartida(const char *nombre_buffer, char *segundos);
void Asigna_Productor(int pid);
void Inicializa_Productor();
void Finaliza_Productor(int pid);
void Crea_Mensaje(int pid);
void Despligue_Total(int proceso_productor);
int Genera_Posicion(int posicion,int tamano_buffer);
void Despliega_Mensaje(int proceso_productor, int llave, time_t fecha, int posicion, int cantidad_productores, int cantidad_consumidores);





