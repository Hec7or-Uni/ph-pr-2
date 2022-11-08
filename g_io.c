#include "g_io.h"

void game_init() {
  gpio_escribir(0, 32, 0);  // Reiniciamos el juego
  gpio_marcar_salida(0, 32);
	gpio_marcar_entrada(3, 7);
	gpio_marcar_entrada(14, 2);
}

void mostrar_jugador(int turno) {
  static uint8_t player = 0;
  gpio_escribir(1, 2, turno);
}

int get_column() {
  int input = gpio_leer(3, 7);
  int msb = MSB(input);
  if ((input & ((1 << msb) - 1)) != 0) return -1;
  return msb;
}

void encender_done() {
  gpio_escribir(16, 1, 1);
  cola_encolar_msg(SetAlarm,ga_auxData(ApagarDone,FALSE,2000));
}

//Se activa al recibir evento ApagarDone
void apagar_done() {
  gpio_escribir(16, 1, 0);
}

void invalid() {
  gpio_escribir(17, 1, 1);
}

void invalidOFF() {
  gpio_escribir(17, 1, 0);
}

void end() {
  gpio_escribir(18, 1, 1);
}

void overflow() {
  gpio_escribir(30, 1, 1);
}

// Se ejecuta al llegar un mensaje Latido
void latido() {
  static uint8_t ON = 0;
  gpio_escribir(31, 1, ON);
  ON = 1 - ON; // alternar estado
}

void latidoOFF() {
  gpio_escribir(31, 1, 0);
}

void check_column() {
  invalid();
}

void gio_tratar_evento(evento_info evento) {
  switch (evento.ID_evento) {
    case PULSACION:
      if (evento.auxData == 2) gio_reset();
      break;
    case PEDIR_VALOR:
      get_column();
      break;
    case DESACTIVAR_LATIDO:
      latidoOFF();
      break;
    case OVERFLOW:
      // ya se vera como llega el evento
      overflow();
      break;
  }
}

void gio_tratar_mensajes(msg_info mensaje) {
  switch (mensaje.ID_msg) {
    case LATIDO:
      latido();
      break;
    case PEDIR_VALOR:
      get_column();
      break;
    case DESACTIVAR_LATIDO:
      latidoOFF();
      break;
    case ENCENDER_INVALIDO:
      invalid();
      break;
    case APAGAR_INVALIDO:
      invalidOFF();
      break;
    case ENCENDER_DONE:
      encender_done();
      break;
    case APAGAR_DONE:
      apagar_done();
      break;
    case CAMBIO_JUGADOR:
      mostrar_jugador(evento.auxData);
      break;
    case FIN;
      end();
      break;
    case OVERFLOW:
      // ya se vera como llega el mensaje
      overflow();
      break;
  }
}