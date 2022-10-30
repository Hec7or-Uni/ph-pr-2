#include "cola_msg.h"

uint8_t first = 0, last = 0, full = 0;
uint32_t colaDATA[COLA_MSG_SIZE];
uint8_t colaID[COLA_MSG_SIZE];

void cola_encolar_msg(uint8_t ID_msg, uint32_t auxData) {
  if (full) {  // overflow
    while (1)
      ;
  }

  if (last == COLA_MSG_SIZE) {
    last = 0;
  }

  colaDATA[last] = auxData;
  colaID[last] = ID_msg;
  last++;
  if (last == first) {
    full = TRUE;
  }
}

msg_info cola_desencolar_msg(void) {
  msg_info msg;

  if (first == COLA_MSG_SIZE) {
    first = 0;
  }

  msg.auxData = colaDATA[first];
  msg.ID_msg = colaID[first];
  first++;
  full = FALSE;
  return msg;
}

int cola_hay_msg(void) { return first != last; }
