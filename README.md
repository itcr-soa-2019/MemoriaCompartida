# MemoriaCompartida
Proyecto 2
Experimentar  con  el  uso de  memoria  compartida  entre  procesos heavyweight. 

Para compilar/crear: 
	make

**Creador: es el que se encarga de crear el buffer compartido por todos los procesos,
inicializa las variables (semaforos y flags), valida los parametros recibidos en la linea de comandos (nombre buffer, tamano o segundos)
./Creador <nombre_buffer> <tamano>

**Productor: se vincula al  buffer del Creador, cada productor recibe como argumentos el nombre del buffer y un parámetro en segundos, tiene tiempos de espera aleatorios para generar mensajes.
./Productor <nombre_buffer> <segundos>

