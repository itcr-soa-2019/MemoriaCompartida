# Memoria Compartida
Instituto Tecnológico de Costa Rica

Sistemas Operativos Avanzados, 2019

Proyecto 2: "Memoria Compartida"

Objetivo: Experimentar  con  el  uso de  memoria  compartida  entre  procesos heavyweight. 

## Compilar programa
Para compilar/crear debe ingresar a la carpeta src en la raiz del proyecto.
```sh
$ make
```

## Creador
Este componente se encarga de crear el buffer compartido por todos los procesos, inicializa las variables (semaforos y flags), valida los parametros recibidos en la linea de comandos (nombre buffer, tamano o segundos).
```sh
$ ./Creador <nombre_buffer> <tamano>
```

## Productor
Se vincula al  buffer del Creador, cada productor recibe como argumentos el nombre del buffer y un parámetro en segundos, tiene tiempos de espera aleatorios para generar mensajes.
```sh
$ ./Productor <nombre_buffer> <segundos>
```

## Consumidor
Se vincula al  buffer del Creador,recibe como argumentos el nombre del buffer y un parámetro en segundos.	En tiempos de espera aleatorios consume los mesajes del buffer. Decrementa el contadores y muestra estadisticas.
```sh
$ ./Consumidor <nombre_buffer> <segundos> 
```

## Finalizador
Cancela todo el sistema de procesos, enviando un mensaje de finalizacion a cada consumidor vivo. Ademas cuando la cantidad de productores y consumidores es cero, el buffer compartido es liberado y lista las estadisticas de su gestion. 
```sh
$ ./Finalizador <nombre_buffer>
```