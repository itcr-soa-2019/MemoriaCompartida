#include "Validador.h"

void validarParamsCreador(int contArgs, char *args[]) {
    if (contArgs != 3) {
        printf("Error en los parámetros: Ingrese el nombre del buffer y cantidad máxima de mensajes.\n");
        exit(1);
    }
    if (atoi(args[2]) <= 0) {
        printf("Error en los parámetros: La cantidad máxima de mensajes debe ser numérica y mayor a 0.\n");
        exit(1);
    }
}

void validarParamsProductor(int contArgs, char *args[]) {
    if (contArgs != 3) {
        printf("Error en los parámetros: Ingrese el nombre del buffer y la media de espera en segundos.\n");
        exit(1);
    }
    if (atoi(args[2]) <= 0) {
        printf("Error en los parámetros: La cantidad de segundos de espera debe ser numérico y mayor a 0.\n");
        exit(1);
    }
}

void validarParamsConsumidor(int contArgs, char *args[]) {
    if (contArgs != 3) {
        printf("Error en los parámetros: Ingrese el nombre del buffer y la media de espera en segundos.\n");
        exit(1);
    }
    if (atoi(args[2]) <= 0) {
        printf("Error en los parámetros: La cantidad de segundos de espera debe ser numérico y mayor a 0.\n");
        exit(1);
    }
}

void validarParamsFinalizador(int contArgs) {
    if (contArgs != 2) {
        printf("Error en los parámetros: Ingrese el nombre del buffer.\n");
        exit(1);
    }
}