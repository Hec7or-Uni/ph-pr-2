#ifndef COLA_ASYNC_H
#define COLA_ASYNC_H
#include <inttypes.h>

#include "msg.h"
#include "utils.h"

#define COLA_MSG_SIZE_PRE 32
#define COLA_MSG_SIZE (uint8_t) COLA_MSG_SIZE_PRE

typedef struct msg_info {
  uint32_t auxData;
  uint8_t ID_msg;
} msg_info;

/**
 * @brief  Funcion que encola un mensaje a la cola de mensajes
 * @param ID_msg Identificador único del mensaje
 * @param auxData Información extra sobre el mensaje
 */
void cola_encolar_msg(uint8_t ID_msg, uint32_t auxData);

/**
 * @brief  Funcion que desencola un mensaje de la cola de mensajes
 * @return Mensaje desencolado
 */
msg_info cola_desencolar_msg(void);

/**
 * @brief  Funcion que comprueba si hay mensajes
 * @return Número de mensajes
 */
int cola_hay_msg(void);

#endif
