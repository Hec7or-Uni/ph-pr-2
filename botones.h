#ifndef BOTONES_H
#define BOTONES_H

#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

#include "cola_asyn.h"
#include "cola_msg.h"
#include "eventos.h"
#include "gestor_alarmas.h"
#include "gpio.h"
#include "msg.h"
#include "utils.h"

enum { BOTON_PULSADO = 1, BOTON_NO_PULSADO = 0 };

/**
 * @brief
 */
void botones_iniciar(void);

/**
 * @brief
 */
void boton1_reset(void);

/**
 * @brief
 */
void boton2_reset(void);

/**
 * @brief
 * @param
 * @return
 */
int boton1_pulsado(void);

/**
 * @brief
 * @param
 * @return
 */
int boton2_pulsado(void);

#endif
