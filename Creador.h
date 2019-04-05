#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include "Buffer.h"
#include "Generalidades.c"



int Crea_Buffer(const char *buffer_name, char *tamano);
void Inicia_Variables();
void Finaliza_Creador();
