#include "g_energia.h"

static int state = NORMAL;

void reset_energy() {
  if (state == IDLE) {
    // Cancelar Latidos
    cola_msg_encolar(Set_Alarm, ga_aux_data(Latido, TRUE, 0));
    state = NORMAL;
  }
  // Resetear alarma de PD
  ga_programar_alarma(ga_aux_data(PowerDown, FALSE, 10000));
}

void idle() {
  if (state == NORMAL) {
    // Activar Latidos
    cola_msg_encolar(Set_Alarm, ga_aux_data(Latido, TRUE, 250));
    state = IDLE;
  }
  PCON = PCON | 0x1;
}

void power_down() {
  EXTWAKE = 6;
  PCON = PCON | 0x2;
  setup_PLL();
  state = NORMAL;
}
