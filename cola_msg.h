#ifndef COLA_MSG_H
#define COLA_MSG_H
#include <inttypes.h>

#include "utils.h"
#include "constantes.h"

enum { COLA_MSG_SIZE = 32 };

typedef struct msg_t {
  uint32_t auxData;
  uint8_t ID_msg;
} msg_t;

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
msg_t cola_desencolar_msg(void);

/**
 * @brief  Funcion que comprueba si hay mensajes
 * @return Número de mensajes
 */
int cola_hay_msg(void);

#endif
