#ifndef COLA_ASYNC_H
#define COLA_ASYNC_H
#include <inttypes.h>

#include "utils.h"

#define COLA_EVENTOS_SIZE_PRE 32
#define COLA_EVENTOS_SIZE (uint8_t) COLA_EVENTOS_SIZE_PRE

typedef struct evento_info {
  uint32_t veces;
  uint32_t auxData;
  uint8_t ID_evento;
} evento_info;

/**
 * @brief  Funcion que encola un evento a la cola de eventos
 * @param ID_msg Identificador único del evento
 * @param veces Número de veces que ha aparecido un evento
 * @param auxData Información extra sobre el evento
 */
void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData);

/**
 * @brief  Funcion que desencola un evento de la cola de eventos
 * @return Evento desencolado
 */
evento_info cola_desencolar_eventos(void);

/**
 * @brief  Funcion que comprueba si hay eventos
 * @return Número de eventos
 */
int cola_hay_eventos(void);

#endif
