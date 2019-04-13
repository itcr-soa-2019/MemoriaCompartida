#include "Finalizador.h"

int main(int argc, char **argv) {	
	int parameters;
	parameters = Validar_Parametros(argc, argv, "Finalizador", "Tamaño_Buffer");
    
    //Cancela_procesos();
}


int Inicia_MemoriaCompartida(const char *nombre_buffer){

}


//Crea un nuevo mensaje en el buffer 
void Crea_Mensaje(int pid){

}


void Cancela_procesos(){
	
    //if((contador_productores==0) && (rptr->contador_consumidores==0)){
        //Imprime_Stats();
        //investigate destroy
    
    if (buf->contador_productores == 0 && buf->contador_consumidores == 0) {
        Imprime_Stats();    
    }
    
	
    /*
    sem_close(sem_buff);
	sem_close(sem_fill);
    sem_close(sem_empt);
    sem_unlink(buffer_sem_name);	
	sem_unlink(fill_sem_name);	
	sem_unlink(empty_sem_name);
    */
}

void Imprime_Stats(){               
    fprintf (stderr, "Cancelando el Sistema de Procesos... \n\n");
    fprintf (stderr, "Proceso:   \n");
    fprintf (stderr, "Total de consumidores activos: \n");
    fprintf (stderr, "Total de productores: \n");
    fprintf (stderr, "Tamaño del buffer: \n");
    fprintf (stderr, "Total de consumidores durante la ejecución: \n");
    fprintf (stderr, "Total de mensajes: \n");
}
