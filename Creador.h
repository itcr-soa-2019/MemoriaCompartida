#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include "Generalidades.h"
#include "Buffer.h"

const int ON=1;
const int ERROR=0;
int tamano_buffer;
struct buffer *buf;
int smo; // share memory object

int Crea_Buffer(const char *buffer_name, char *tamano);
void Inicia_Variables();
void Finaliza_Creador();

