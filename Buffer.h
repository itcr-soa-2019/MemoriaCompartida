struct buffer {
    int tamano_buffer;
    int contador_productores;
    int contador_consumidores;
    int actual_lectura;
    int actual_escritura;
    unsigned int mensajes_totales;
    unsigned int consumidores_totales;
};
