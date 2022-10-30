#include "cola_asyn.h"

uint8_t first = 0, last = 0, full = 0;
uint32_t colaVECES[COLA_EVENTOS_SIZE];
uint32_t colaDATA[COLA_EVENTOS_SIZE];
uint8_t colaID[COLA_EVENTOS_SIZE];

void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData) {
  if (full) {  // overflow
    while (1)
      ;
  }

  if (last == COLA_EVENTOS_SIZE) {
    last = 0;
  }

  colaVECES[last] = veces;
  colaDATA[last] = auxData;
  colaID[last] = ID_evento;
  last++;
  if (last == first) {
    full = TRUE;
  }
}

evento_info cola_desencolar_eventos(void) {
  evento_info evento;

  if (first == COLA_EVENTOS_SIZE) {
    first = 0;
  }

  evento.veces = colaVECES[first];
  evento.auxData = colaDATA[first];
  evento.ID_evento = colaID[first];
  first++;
  full = FALSE;
  return evento;
}

int cola_hay_eventos(void) { return first != last; }
