#ifndef GESTOR_ENERGIA_H
#define GESTOR_ENERGIA_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>
#include "utils.h"
#include "msg.h"
#include "gestor_alarmas.h"
#include "cola_msg.h"

enum MCU_MODE { NORMAL, IDLE };

/**
 * @brief Pone el procesador en modo bajo consumo.
 * En idle el procesador se para, pero los periféricos del chip, como el
 * temporizador, siguen activos y lo pueden despertar al
 * realizar una interrupción.
 */
void idle(void);

/**
 * @brief Pone al procesador a dormir.
 * En el estado power-down los periféricos también entran en bajo consumo y
 * dejan de funcionar pero se sigue manteniendo el estado.
 */
void power_down(void);

/**
 * @brief Pone al procesador en modo normal.
 */
void reset_energy(void);

#endif
