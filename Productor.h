#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include "Buffer.h"



const int ERROR=0;
const int ON=1;
struct buffer *buf;
int total_mensajes;
int tamano_buffer;
int smo;

int Inicia_MemoriaCompartida(const char *nombre_buffer, char *segundos);
void Crea_Productor();
void Inicializa_Productor();
void Asigna_Productor();
void Finaliza_Productor();
void Crea_Mensaje();
void Despligue_Total();
void Despliega_Mensaje();
