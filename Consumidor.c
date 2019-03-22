
#include "Consumidor.h"


int main(int argc, char **argv) {
	
}

int Inicia_MemoriaCompartida (const char *nombre_buffer, char *segundos) {

}

void Inicializa_Consumidor(double segundos){
	
}

//Asigna un nuevo productor en la memoria compartida
void Asigna_Consumidor(int pid){
	// incrementar totales
}


//Liberar o suspende la memoria y despliega estadisticas
void Finaliza_Consumidor(int pid){
	// agregar metodo para finalizar
	Imprime_Stats(pid);
}

//Crea un nuevo mensaje en el buffer
void Crea_Mensaje(int process){
	// crear mensaje
    //Despliega_Mensaje(parameters!!);
	//Valida_PID();

}

void Despliega_Mensaje(int process, int key, time_t fecha, int cantidad_prod, int cantidad_cons){
	char buff[20];
	struct tm * timeinfo;
	timeinfo = localtime(&fecha);
	fprintf (stderr, "\tNuevo Mensaje Leído \n");
    fprintf (stderr,"\tIdentificador: %i\n", process);
    fprintf (stderr, "\tLlave: %i\n",key);
    fprintf (stderr, "\tFecha y Hora de creacion: %s\n",buff);
    strftime(buff,sizeof(buff),"%Y-%m-%d %H:%M:%S",timeinfo);
    fprintf (stderr, "\tTotal acumulado de mensajes: %i\n",total_mensajes);
    fprintf (stderr, "\tCantidad de productores: %i\n",cantidad_prod);
    fprintf (stderr, "\tCantidad de consumidores: %i\n",cantidad_cons);

}


//Valida si llave del mensaje leído es igual al PID del consumidor%5
int Valida_PID(int key, int process)
{
	int module=process%5;
	if(module==key)
	{
		fprintf(stderr, "Consumidor termina por llave %i, PID: %i, Modulo:  %i \n" , key, process, module);
		key_exit=ON;
		return OFF;
	}
	else
	{
		return ON;
	}
}

void Imprime_Stats(int process){
                
}

