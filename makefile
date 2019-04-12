HEADERS = Buffer.h Mensaje.h DistExponencial.h Generalidades.h

all: Creador Productor Consumidor $(HEADERS)

Creador: Creador.c $(HEADERS)
	gcc -o Creador Creador.c -lrt -lpthread -lm

Productor: Productor.c $(HEADERS)
	gcc -o Productor Productor.c -lrt -lpthread -lm

Consumidor: Consumidor.c $(HEADERS)
	gcc -o Consumidor Consumidor.c -lrt -lpthread -lm

Clean:
	rm Creador Productor Consumidor
