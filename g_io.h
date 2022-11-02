#ifndef GESTOR_IO_H
#define GESTOR_IO_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "gpio.h"
#include "utils.h"

/**
 * @brief Inicializa el gestor de IO.
 */
void game_init(void);

/**
 * @brief Indicador del jugador X (1 o 2).
 * @param turno jugaador 1 o jugador 2.
 */
void jugador(int turno);

/**
 * @brief columna seleccionada como jugada
 */
int getValue(void);

/**
 * @brief Jugada realizada.
 */
void done(void);

/**
 * @brief Jugada no valida.
 */
void invalid(void);

/**
 * @brief Final de partida.
 */
void end(void);

/**
 * @brief Overflow
 */
void overflow(void);

/**
 * @brief Latido modo idle
 */
void latido(void);

#endif
