#ifndef GESTOR_ENERGIA_H
#define GESTOR_ENERGIA_H

#include <inttypes.h>
#include "utils.h"
#include "msg.h"
#include "eventos.h"
#include "g_alarmas.h"
#include "cola_msg.h"
#include "cola_asyn.h"
#include "power.h"

enum estados { NORMAL, IDLE };

/**
 * @brief Pone al procesador a dormir.
 * En el estado power-down los periféricos también entran en bajo consumo y
 * dejan de funcionar pero se sigue manteniendo el estado.
 */
void g_energia_power_down(void);

/**
 * @brief Pone al procesador en modo normal.
 */
void g_energia_reset(void);

/**
 * @brief Pone el procesador en modo bajo consumo.
 * En g_energia_idle el procesador se para, pero los periféricos del chip, como el
 * temporizador, siguen activos y lo pueden despertar al
 * realizar una interrupción.
 */
void g_energia_idle(void);

/**
 * @brief Tratamiento de eventos del módulo del gestor de energía
 * @param evento Evento a tratar
 */
void g_energia_tratar_evento(evento_t evento);

/**
 * @brief Tratamiento de mensajes del módulo del gestor de energía
 * @param mensaje Mensaje a tratar
 */
void g_energia_tratar_mensaje(msg_t mensaje);

#endif
