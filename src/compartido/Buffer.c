#include <sys/mman.h>
#include "Buffer.h"

buffer_t* inicializarBuffer(buffer_t* buffer, char* nombre, size_t tamano, int maxMensajes) {
    buffer->nombre = nombre;
    buffer->tamano = tamano;
    buffer->maxMensajes = maxMensajes;
    buffer->activo = 1;
    buffer->contTotalMensajes = 0;
    buffer->contMensajesLeidos = 0;
    buffer->contProductores = 0;
    buffer->contPonsumidores = 0;

    // inicializar array de mensajes

    // sincronizar
    msync(buffer, buffer->tamano, MS_SYNC);
}

