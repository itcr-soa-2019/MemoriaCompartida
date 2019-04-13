#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "Buffer.h"
#include "Generalidades.c"

const int OFF=0;
const int ERROR=0;
struct buffer *buf;
int fd;
int tamano_buffer;

int Inicia_MemoriaCompartida(const char *nombre_buffer);
void Crea_Mensaje(int pid);
void Cancela_procesos();
void Imprime_Stats();