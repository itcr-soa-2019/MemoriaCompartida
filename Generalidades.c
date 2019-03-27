#include "Generalidades.h"

// metodos para validar los parametros de entrada


int Validar_Parametros(int argc, char **argv, char* Nombre, char* Argumento)
{
	int val=0;
	//Llamada: creador + nombre buffer + media en segundos

	/***** Validacion de argumentos *****/
	if (argc < 3) {
		uso(1, Nombre, Argumento, "Faltan Parámetros." ) ;
	}
	if (argc > 3){
		uso(1, Nombre, Argumento, "Ha ingresado más parámetros." ) ;
	}
	if (argc == 3)
	{
		val = atoi(argv[2]);
		if (val <= 0)
		{
			uso(1, Nombre, Argumento, "El segundo parámetro debe ser numérico y mayor a 0." ) ;
		}
	}
	return val;
}

