
#include <stdio.h>
#include <string.h>


void indicaciones( int exitval, char* nombre, char* argumento, char* error)
{
	fprintf(stderr, "\n** Indicaciones del uso: **\n\n");
	if (strlen(argumento)>0) {
		fprintf(stderr, "\nIngrese los parametros de la siguiente manera: %s Nombre_Buffer %s\nError: %s \n\n" ,nombre, argumento, error);
	} else {
		fprintf(stderr, "\nIngrese los parametros de la siguiente manera: %s Nombre_Buffer \nError: %s \n\n", nombre, error);
	}
	exit(exitval);
}


int Validar_Parametros(int argc, char **argv, char* nombre, char* argumento)
{
	int val=0;
	if (argc < 3) {
		indicaciones(1, nombre, argumento, "Faltan parámetros de entrada." ) ;
	}
	if (argc > 3){
		indicaciones(1, nombre, argumento, "Ha ingresado más parámetros." ) ;
	}
	if (argc == 3)
	{
		val = atoi(argv[2]);
		if (val <= 0)
		{
			indicaciones(1, nombre, argumento, "El tamano del buffer debe ser numérico y mayor a 0." ) ;
		}
	}
	return val;
}

int Genera_Llave_Aleatoria(){
	return rand()%5;
}


