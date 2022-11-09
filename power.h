#ifndef POWER_H
#define POWER_H

#include <LPC210x.H> /* LPC210x definitions */

/**
 * @brief LLama a funci�n ASM establecida en Startup.s para restablecer
 * la configuraci�n del PLL
 */
void setup_PLL(void);

/**
 * @brief Pone al procesador a dormir.
 * En el estado power-down los perif�ricos tambi�n entran en bajo consumo y
 * dejan de funcionar pero se sigue manteniendo el estado.
 */
void power_down(void);

/**
 * @brief Pone el procesador en modo bajo consumo.
 * En g_energia_idle el procesador se para, pero los perif�ricos del chip, como el
 * temporizador, siguen activos y lo pueden despertar al
 * realizar una interrupci�n.
 */
void idle(void);

#endif
