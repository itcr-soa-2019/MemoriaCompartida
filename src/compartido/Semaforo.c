#include "Semaforo.h"

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