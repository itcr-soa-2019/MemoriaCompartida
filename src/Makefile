CC= gcc
TARGET= bin
CFLAGS= -std=gnu99 -g -Wl,--export-dynamic
LIBS= -pthread -lm

all: compile_compartido compile_creador compile_productor compile_consumidor compile_finalizador

compile_compartido:
	(cd compartido; make)

compile_creador: creador/Creador.c compartido/lib_compartida
	$(CC) $(CFLAGS) -o $(TARGET)/Creador creador/Creador.c compartido/lib_compartida $(LIBS)

compile_productor:
	#$(CC) $(CFLAGS) -o $(TARGET)/Productor productor/Productor.c compartido/lib_compartida $(LIBS)

compile_consumidor:
	#$(CC) $(CFLAGS) -o $(TARGET)/Consumidor consumidor/Consumidor.c compartido/lib_compartida $(LIBS)

compile_finalizador:
	#$(CC) $(CFLAGS) -o $(TARGET)/Finalizador finalizador/Finalizador.c compartido/lib_compartida $(LIBS)

clean:
	rm -rf **/*.o $(TARGET)/Creador #$(TARGET)/Productor $(TARGET)/Consumidor $(TARGET)/Finalizador
