#include "semaforo_interrupciones.h"

static uint32_t recover;

void bloquear_interrupciones() {
	recover = VICIntEnable;
	VICIntEnable = 0;
}

void liberar_interrupciones() {
	VICIntEnable = recover;
}
