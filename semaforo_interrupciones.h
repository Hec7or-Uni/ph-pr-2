#ifndef __SEMAFORO_INTERRUPCIONES__
#define __SEMAFORO_INTERRUPCIONES__

#include <inttypes.h>
#include <LPC210x.H>

static uint32_t recover;

/**
 * @brief Bloquea las interrupciones
 */
void bloquear_interrupciones(void);

/**
 * @brief Libera las interrupciones bloqueadas
 */
void liberar_interrupciones(void);

#endif
