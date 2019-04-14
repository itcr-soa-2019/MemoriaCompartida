#include "Buffer.h"

int Existe_Buffer(char *nombre_buffer){
    int fd = open(nombre_buffer, O_RDWR, (mode_t)0600);
	if (fd == -1) {
		return 0;
	}	
    return 1;
}