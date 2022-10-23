#include <LPC210x.H> /* LPC210x definitions */
#include <inttypes.h>

/**
 * @brief Programa un contador para que pueda ser utilizado.
 */
void temporizador_iniciar();

/**
 * @brief Inicia la cuenta de un contador de forma indefinida.
 */
void temporizador_empezar();

/**
 * @brief Lee el tiempo que lleva contando el contador desde la última vez que se ejecutó
 * temporizador_empezar y lo devuelve en microsegundos.
 */
uint32_t temporizador_leer();

/**
 * @brief Detiene el contador y devuelve el tiempo transcurrido desde temporizador_empezar
 */
uint32_t temporizador_parar();

/**
 * @brief Programa el reloj para que encole un evento periódicamente. El periodo se indica en ms.
 * @param periodo Periodo en ms.
 */
void temporizador_reloj(int periodo);