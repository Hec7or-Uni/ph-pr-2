#include "botones.h"

void g_boton_tratar_evento(evento_t evento) {
	switch (evento.ID_evento) {
    case PULSACION:
			if (evento.auxData == 1) {
				cola_encolar_msg(SET_ALARM, g_alarma_crear(RESET_1, TRUE, 10));
			}
			else if (evento.auxData == 2) {
				cola_encolar_msg(SET_ALARM, g_alarma_crear(RESET_2, TRUE, 10));
			}
      break;
  }
}

void g_boton_tratar_mensaje(msg_t mensaje) {
  switch (mensaje.ID_msg) {
		case INICIO:
			botones_iniciar();
			break;
    case RESET_1:
      if (!boton1_pulsado()) {
        boton1_reset();
        cola_encolar_msg(SET_ALARM,g_alarma_borrar(RESET_1));
      }
      break;
    case RESET_2:
      if (!boton2_pulsado()) {
        boton2_reset();
        cola_encolar_msg(SET_ALARM,g_alarma_borrar(RESET_2));
      }
      break;
  }
}
