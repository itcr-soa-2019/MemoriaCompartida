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

**Consumidor: se vincula al  buffer del Creador,recibe como argumentos el nombre del buffer y un parámetro en segundos.	En tiempos de espera aleatorios consume los mesajes del buffer. Decrementa el contadores y muestra estadisticas.

./Consumidor <nombre_buffer> <segundos>

**Finalizador: Se encarga de cancelar todo el sistema de procesos, enviando mensajes de finalización a cada consumidor vivo usando el buffer compartido, le indica a los productores que cesen actividades. Una vez que la cantidad de productores y consumidores llega a cero, el buffer compartido es liberado.

./Finalizador <nombre_buffer> <tamano>
