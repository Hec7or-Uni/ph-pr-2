#ifndef GESTOR_IO_H
#define GESTOR_IO_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "gpio.h"
#include "utils.h"
#include "cola_asyn.h"
#include "cola_msg.h"

/**
 * @brief Inicializa el gestor de IO.
 */
void game_init(void);

/**
 * @brief Indicador del jugador X (1 o 2).
 * @param turno jugaador 1 o jugador 2.
 */
void alternar_jugador(int turno);

/**
 * @brief columna seleccionada como jugada
 * @return columna seleccionada o -1 si no hay ninguna o más de 1.
 */
int get_column(void);

/**
 * @brief Indicar jugada realizada.
 */
void encender_done(void);

/**
 * @brief Apagar indicador de jugada realizada.
 */
void apagar_done(void);

/**
 * @brief Indicar jugada no valida.
 */
void invalid(void);

void invalidOFF(void);

/**
 * @brief Indicar final de partida.
 */
void end(void);

/**
 * @brief Indicar overflow
 */
void overflow(void);

/**
 * @brief Alternar led indicador de modo idle
 */
void latido(void);

/**
 * @brief Apagar indicador de modo idle
 */
void latidoOFF(void);

#endif
