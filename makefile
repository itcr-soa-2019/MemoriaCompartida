HEADERS = Buffer.h Mensaje.h DistExponencial.h Generalidades.h

all: Creador Productor $(HEADERS)

Creador: Creador.c $(HEADERS)
	gcc -o Creador Creador.c -lrt -lpthread -lm

Productor: Productor.c $(HEADERS)
	gcc -o Productor Productor.c -lrt -lpthread -lm

Clean:
	rm Creador Productor