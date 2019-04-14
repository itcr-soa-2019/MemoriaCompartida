#include "DistExponencial.h"

double DistExponencial_Espera (int segundos) {
    int val = rand();
    while (val == RAND_MAX)
        val = rand();
    double decimal = (double) val / RAND_MAX;
    return log (1 - decimal) * (-segundos);
}
