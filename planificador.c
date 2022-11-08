#include "botones.h"
#include "cola_asyn.h"
#include "cola_msg.h"
#include "eventos.h"
#include "g_energia.h"
#include "g_io.h"
#include "gestor_alarmas.h"
#include "gpio.h"
#include "msg.h"
#include "tableros.h"
#include "utils.h"

void prototipo_planificador() {
  int hay_evento, hay_msg;
  int resetPD;
  ga_iniciar();
  botones_iniciar();
  reset_energy();
  cola_encolar_msg(Set_Alarm, ga_aux_data(CheckColumn, TRUE, 100));
  while (1) {
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
          if (evento.auxData == 1) {
            realizar_jugada();
          } else if (evento.auxData == 2) {
            reset_game();
          }
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
        case Latido:
          latido();
          break;
        case ApagarRealizada:
          apagar_done();
          break;
        case CheckColumn:
          check_column();
          break;
        case END:
          protocoloFin();
      }
    }

    if (resetPD) reset_energy();

    if (!hay_evento && !hay_msg) idle();
  }
}

void check_column() {
  int column = get_column();
  if (column == -1) {
    invalid();
    return;
  }

  // la cuadricula no se conoce en este scope
  uint8_t row = C4_calcular_fila(cuadricula_1, column);
  if (!C4_fila_valida(row)) {
    invalid();
    return;
  }

  invalidOFF();
}

void realizar_jugada() {
  static uint8_t colour = 1;
  uint8_t column, row;

  column = get_column();
  if (column == -1) {
    return;
  }

  // la cuadricula no se conoce en este scope
  row = C4_calcular_fila(cuadricula_1, column);
  if (!C4_fila_valida(row)) {
    return;
  }

  C4_actualizar_tablero(cuadricula_1, row, column, colour);
  if (C4_verificar_4_en_linea(cuadricula_1, row, column, colour, 0) ||
      C4_comprobar_empate(cuadricula_1)) {
    cola_encolar_eventos(END, 1, colour);
  }
}