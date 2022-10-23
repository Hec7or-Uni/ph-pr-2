#ifndef COLA_ASYNC_H
#define COLA_ASYNC_H
#include <inttypes.h>
#include "utils.h"

#define COLA_SIZE_PRE 32
#define COLA_SIZE (uint8_t) COLA_SIZE_PRE
				
typedef struct
{
  uint32_t veces;
  uint32_t auxData;
  uint8_t ID_evento;
} cola_asyn;

/**
 * @brief  Funcion que encola un evento a la cola de eventos
 */
void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData);

/**
 * @brief  Funcion que desencola un evento de la cola de eventos
 */
cola_asyn cola_desencolar_eventos(void);

/**
 * @brief  Funcion que comprueba si hay eventos
 */
int cola_hay_eventos(void);

#endif
