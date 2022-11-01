#include "g_io.c"

void game_init() {
  gpio_escribir(0, 32, 0);  // Reiniciamos el juego
  gpio_marcar_salida(0, 32);
	gpio_marcar_entrada(3, 7);
	gpio_marcar_entrada(14, 2);
}

void jugador(int turno) {
  gpio_escribir(1, 2, turno);
}

int getValue() {
  int num = gpio_leer(3, 7); // 0001000
  return 0;
}

void done() {
  gpio_escribir(16, 1, 1);
}

void invalid() {
  gpio_escribir(17, 1, 1);
}

void end() {
  gpio_escribir(18, 1, 1);
}

void overflow() {
  gpio_escribir(30, 1, 1);
}

//Se ejecuta al llegar un mensaje Latido
void latido() {
  static uint8_t ON = FALSE;
  if (ON) gpio_escribir(31, 1, 1);
  else gpio_escribir(31, 1, 0);
  ON = 1 - ON; // alternar estado
}