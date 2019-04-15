CC=gcc
CFLAGS= -std=gnu99 -g -Wl,--export-dynamic
LIBS = -lm -pthread
CHECK=-Wall -Wextra

all: Buffer.c
	$(CC) -shared -fpic Buffer.c Mensaje.c Semaforo.c -o lib_compartida
