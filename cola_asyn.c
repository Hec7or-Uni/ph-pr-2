#include "cola_asyn.h"

typedef struct
{
  uint32_t veces;
  uint32_t auxData;
  uint8_t ID_evento;
} cola_asyn;

uint8_t first = 0, last = 0, full = 0;
uint32_t colaVECES[COLA_SIZE];
uint32_t colaDATA[COLA_SIZE];
uint8_t colaID[COLA_SIZE];

void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData)
{
  if (full)
  { // overflow
    while (1)
      ;
  }
  if (last == COLA_SIZE)
  {
    last = 0;
  }
  colaVECES[last] = veces;
  colaDATA[last] = auxData;
  colaID[last] = ID_evento;
  last++;
  if (last == first)
  {
    full = TRUE;
  }
}

cola_asyn cola_desencolar_eventos(void)
{
  cola_asyn cola;
  if (first == COLA_SIZE)
  {
    first = 0;
  }
  cola.veces = colaVECES[first];
  cola.auxData = colaDATA[first];
  cola.ID_evento = colaID[first];
  first++;
  full = FALSE;
  return cola;
}

int cola_hay_eventos(void)
{
  return first != last;
}
