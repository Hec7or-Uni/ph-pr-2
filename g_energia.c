#include "g_energia.h"

static int estado = NORMAL;

void setup_PLL(void);

void g_energia_power_down() {
  power_down();
  setup_PLL();
  estado = NORMAL;
}

void g_energia_reset() {
  if (estado == IDLE) {
    // Cancelar LATIDO
    cola_encolar_msg(SET_ALARM, g_alarma_crear(LATIDO, TRUE, 0));
    cola_encolar_msg(APAGAR_LATIDO, 0);
    estado = NORMAL;
  }
  // Resetear alarma de POWER_DOWN
  cola_encolar_msg(SET_ALARM, g_alarma_crear(POWER_DOWN, FALSE, 10000));
}

void g_energia_idle() {
  if (estado == NORMAL) {
    // Activar LATIDO
    cola_encolar_msg(SET_ALARM, g_alarma_crear(LATIDO, TRUE, 250));
    estado = IDLE;
  }
  idle();
}

void g_energia_tratar_evento(evento_t evento) {
  switch (evento.ID_evento) {
    case PULSACION:
      g_energia_reset();
      break;
  }
}

void g_energia_tratar_mensaje(msg_t mensaje) {
  switch (mensaje.ID_msg) {
    case INICIO:
      cola_encolar_msg(SET_ALARM, g_alarma_crear(POWER_DOWN, FALSE, 10000));
      break;
    case POWER_DOWN:
      g_energia_power_down();
      cola_encolar_msg(SET_ALARM, g_alarma_crear(POWER_DOWN, FALSE, 10000));
      break;
  }
}
