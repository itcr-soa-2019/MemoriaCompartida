#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "Creador.h"
#include "../compartido/Buffer.h"
#include "../compartido/Semaforo.h"

int main (int argc, char *argv[]) {
    // leer y validar parámetros
    validarParamsCreador(argc, argv);
    char* nombreBuffer = argv[1];
    int maxMensajes = atoi(argv[2]);

    // crear semáforos
    sem_t* semaforoOcupado = crearSemaforo(nombreSemaforoOcupado, 1);
    sem_t* semaforoVacio = crearSemaforo(nombreSemaforoVacio, maxMensajes);
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
    return 0;
}
