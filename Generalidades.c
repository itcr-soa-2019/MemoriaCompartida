
#include <stdio.h>
#include <string.h>


void uso( int exitval, char* nombre, char* argumento, char* error)
{
	fprintf(stderr, "\n\
		SISTEMAS OPERATIVOS AVANZADOS\n\
		\n\
		"
	);

	if (strlen(argumento)>0){
			fprintf(stderr, "\n\
				Uso: %s Nombre_Buffer %s\n\
				Error: %s \n\
				\n\
				"
				,nombre, argumento, error);
	}
	else
	{
		fprintf(stderr, "\n\
			Uso: %s Nombre_Buffer \n\
			Error: %s \n\
			\n\
			"
				,nombre, error);
	}
	exit(exitval);
}


int Validar_Parametros(int argc, char **argv, char* nombre, char* argumento)
{
	int val=0;
	if (argc < 3) {
		uso(1, nombre, argumento, "Faltan Parámetros." ) ;
	}
	if (argc > 3){
		uso(1, nombre, argumento, "Ha ingresado más parámetros." ) ;
	}
	if (argc == 3)
	{
		val = atoi(argv[2]);
		if (val <= 0)
		{
			uso(1, nombre, argumento, "El segundo parámetro debe ser numérico y mayor a 0." ) ;
		}
	}
	return val;
}

