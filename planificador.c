#include "botones.h"
#include "cola_asyn.h"
#include "cola_msg.h"
#include "eventos.h"
#include "gestor_alarmas.h"
#include "gpio.h"
#include "msg.h"
#include "utils.h"
#include "g_energia.h"

void prototipo_planificador() {
  int hay_evento, hay_msg;
  int resetPD;
  ga_iniciar();
  botones_iniciar();
  reset_energy();
  for (;;) {
    resetPD = TRUE;
		hay_evento = cola_hay_eventos();
    if (hay_evento) {
      // reset alarma
      evento_info evento = cola_desencolar_eventos();
      switch (evento.ID_evento) {
        case Timer_Event:
          resetPD = FALSE;
          ga_comprobar_alarmas();
          break;
        case Pulsacion:
          // Se ha pulsado algo
          break;
      }
    }
		hay_msg = cola_hay_msg();
    if (hay_msg) {
      // reset alarma
      msg_info msg = cola_desencolar_msg();
      switch (msg.ID_msg) {
        case Set_Alarm:
          resetPD = FALSE;
          ga_programar_alarma(msg.auxData);
          break;
        case Reset1:
          if (!boton1_pulsado()) {
            boton1_reset();
            ga_programar_alarma(ga_aux_data(Reset1, 0, 0));
          }
          break;
        case Reset2:
          if (!boton2_pulsado()) {
            boton2_reset();
            ga_programar_alarma(ga_aux_data(Reset2, 0, 0));
          }
          break;
        case PowerDown:
          power_down();
          break;
      }
    }

    if (resetPD) reset_energy();

    if (!hay_evento && !hay_msg) idle();
  }
}
