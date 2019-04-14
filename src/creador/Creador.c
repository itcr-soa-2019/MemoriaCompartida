#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "Creador.h"
#include "../compartido/Buffer.h"

/**
 * 
 * Para correrlo sin el makefile:
 * gcc Creador.c ../compartido/Buffer.c -o Creador -lrt -lpthread -lm
 * 
 * */

int main (int argc, char *argv[]) {
    // leer y validar parámetros
    validarParams(argc, argv);
    char* nombreBuffer = argv[1];
    int maxMensajes = atoi(argv[2]);

    // crear semáforos
    sem_t* semaforoOcupado = crearSemaforo(nombreSemaforoOcupado, 1);
    sem_t* semaforoVacio = crearSemaforo(nombreSemaforoVacio, maxMensajes - 1);
    sem_t* semaforoLleno = crearSemaforo(nombreSemaforoLleno, 0);

    // crear región compartida
    int descriptorArchivo = open(nombreBuffer, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (descriptorArchivo == -1) {
        printf("Error creando archivo compartido\n");
        exit(1);
    }
    __off_t offset = lseek(descriptorArchivo, sizeof(buffer_t) + sizeof(mensaje_t) * maxMensajes - 1, SEEK_SET);
    if (offset == -1) {
        close(descriptorArchivo);
        printf("Error creando archivo compartido\n");
        exit(1);
    }
    ssize_t result = write(descriptorArchivo, "", 1);
    if (result != 1) {
        close(descriptorArchivo);
        printf("Error creando archivo compartido\n");
        exit(1);
    }

    size_t tamanoMapping = (size_t) (offset + 1);
    buffer_t* buffer = (buffer_t*) mmap(NULL, tamanoMapping, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, descriptorArchivo, 0);
    if (buffer == MAP_FAILED) {
        close(descriptorArchivo);
        sem_close(semaforoOcupado);
        sem_unlink(nombreSemaforoOcupado);
        printf("Error mapeando memoria compartida\n");
        exit(1);
    }
    inicializarBuffer(buffer, nombreBuffer, tamanoMapping, maxMensajes);

    printf("Creador completado!!\n");
}

void validarParams(int contArgs, char *args[]) {
    if (contArgs != 3) {
        printf("Error en los parámetros: Ingrese el nombre del buffer y cantidad máxima de mensajes.\n");
        exit(1);
    }

    if (atoi(args[2]) <= 0) {
        printf("Error en los parámetros: La cantidad máxima de mensajes debe ser numérica y mayor a 0.\n");
        exit(1);
    }
}

sem_t* crearSemaforo(char* nombre, int valor) {
    sem_unlink(nombre);
    sem_t* semaforo = sem_open(nombre, O_CREAT, 0644, valor);
    if (semaforo == SEM_FAILED) {
        printf("Error creando semáforo\n");
        exit(1);
    }
    return semaforo;
}

sem_t* getSemaforo(char* nombre) {
    sem_t* semaforo = sem_open(nombre, 0, 0644, 0);
    if (semaforo == SEM_FAILED) {
        printf("Error obteniendo semáforo\n");
        exit(1);
    }
    return semaforo;
}