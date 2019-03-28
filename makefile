HEADERS = Buffer.h Mensaje.h DistExponencial.h Generalidades.h

all: Creador $(HEADERS)

Creador: Creador.c $(HEADERS)
	gcc -o Creador Creador.c -lrt -lpthread -lm


Clean:
	rm Creador 