#include "botones.h"
#include "cola_asyn.h"
#include "cola_msg.h"
#include "eventos.h"
#include "gestor_alarmas.h"
#include "gpio.h"
#include "msg.h"
#include "utils.h"

void prototipo_planificador() {
  ga_iniciar();
  botones_iniciar();
  for (;;) {
    if (cola_hay_eventos()) {
      evento_info evento = cola_desencolar_eventos();
      switch (evento.ID_evento) {
        case Timer_Event:
          ga_comprobar_alarmas();
          break;
        case Pulsacion:
          // Se ha pulsado algo
          break;
      }
    }
    if (cola_hay_msg()) {
      msg_info msg = cola_desencolar_msg();
      switch (msg.ID_msg) {
        case Set_Alarm:
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
      }
    }
  }
}