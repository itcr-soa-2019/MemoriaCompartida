#include "Buffer.h"
#include <semaphore.h>

const int ON=1;
const int ERROR=0;
int tamano_buffer;
struct buffer *buf;
int smo; // share memory object

int Crea_Buffer(const char *buffer_name, char *tamano);
void Inicia_Variables();
void Finaliza_Creador();

