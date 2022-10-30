#ifndef UTILS_H
#define UTILS_H

/* Definiciones para valores muy utilizados */
enum { FALSE = 0, TRUE = 1, ERROR = 0xFF };

/* Comprobar si es potencia de 2*/
#define POWER_OF_2(x) ((x != 0) && !(x & (x - 1)))

#endif
