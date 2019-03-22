#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "Buffer.h"
#include "Mensaje.h"

const int ERROR=0;
const int ON=1;
const int OFF=0;
struct buffer *buf;
int fd;
double tiempo_total_bloqueo;
double tiempo_total_espera; 

int key_exit;
int tamano_buffer;
int total_mensajes;
int exec=1;
// pid : process id

int Inicia_MemoriaCompartida(const char *nombre_buffer, char *segundos);
void Inicializa_Consumidor();
void Asigna_Consumidor(int pid);
void Finaliza_Consumidor(int pid);
void Crea_Mensaje(int process);
int  Valida_PID(int key, int process);
void Despliega_Mensaje(int process, int key, time_t fecha, int cantidad_prod, int cantidad_cons);
void Imprime_Stats(int process);
