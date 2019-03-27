HEADERS = Buffer.h Mensaje.h DistExponencial.h Generalidades.h

all: Creador Productor Consumidor Finalizador $(HEADERS)

Creador: Creador.c $(HEADERS)
	gcc -o Creador Creador.c -lrt -lpthread -lm

Finalizador: Finalizador.c $(HEADERS)
	gcc -o Finalizador Finalizador.c -lrt -lpthread -lm

Clean:
	rm Creador Consumidor Productor Finalizador