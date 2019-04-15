CC= gcc
CFLAGS= -std=gnu99 -g -Wl,--export-dynamic
LIBS= -pthread -lm

all: compile_compartido compile_creador compile_productor compile_consumidor compile_finalizador

compile_compartido:
	(cd compartido; make)

compile_creador: creador/Creador.c compartido/lib_compartida
	$(CC) $(CFLAGS) -o Creador creador/Creador.c compartido/lib_compartida $(LIBS)

compile_productor:
	$(CC) $(CFLAGS) -o Productor productor/Productor.c compartido/lib_compartida $(LIBS)

compile_consumidor:
	#$(CC) $(CFLAGS) -o Consumidor consumidor/Consumidor.c compartido/lib_compartida $(LIBS)

compile_finalizador:
	#$(CC) $(CFLAGS) -o Finalizador finalizador/Finalizador.c compartido/lib_compartida $(LIBS)

clean:
	rm -rf **/*.o Creador #Productor Consumidor Finalizador
