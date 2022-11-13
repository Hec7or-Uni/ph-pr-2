#include "cola_asyn.h"
#include "cola_msg.h"
#include "g_energia.h"
#include "g_io.h"
#include "g_alarmas.h"
#include "g_boton.h"
#include "conecta4_2022.h"

void prototipo_planificador(void) {
  int hay_evento, hay_msg;
	cola_encolar_msg(INICIO,0);
  while (1) {
    hay_evento = cola_hay_eventos();
    if (hay_evento) {
      evento_t evento = cola_desencolar_eventos();
      g_alarma_tratar_evento(evento);
      g_energia_tratar_evento(evento);
			g_boton_tratar_evento(evento);
			g_io_tratar_evento(evento);
    }
    hay_msg = cola_hay_msg();
    if (hay_msg) {
      msg_t msg = cola_desencolar_msg();
      /*if (msg.ID_msg == RESET) {
        cola_vaciar_eventos();
        cola_vaciar_msg();
      }*/
      g_alarma_tratar_mensaje(msg);
      g_energia_tratar_mensaje(msg);
      g_boton_tratar_mensaje(msg);
			g_io_tratar_mensaje(msg);
      conecta4_tratar_mensaje(msg);
      
    }
    if (!hay_evento && !hay_msg) g_energia_idle();
  }
}
