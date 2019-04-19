#include <stdio.h>
#include <stdlib.h>

#ifndef Validador_h
#define Validador_h

void validarParamsCreador(int contArgs, char *args[]);
void validarParamsProductor(int contArgs, char *args[]);
void validarParamsConsumidor(int contArgs, char *args[]);
void validarParamsFinalizador(int contArgs);

#endif