#include "gpio.h"

/*
 IOPIN: para leer los de entrada
 IODIR: si el bit tiene un 0 es de entrada, y si tiene un 1 es de salida
 IOSET: 1s donde queremos poner 1s
 IOCLR: 1s donde queremos poner 0s
 */

void gpio_iniciar(void) {
  // Limpiamos los pines
  IODIR = 0xFFFFFFFF;
  IOCLR = 0xFFFFFFFF;
}

int gpio_leer(int bit_inicial, int num_bits) {
  uint32_t mask = ((1 << num_bits) - 1) << bit_inicial;
  return (IOPIN & mask) >> bit_inicial;
}

void gpio_escribir(int bit_inicial, int num_bits, int valor) {
  uint32_t maskON = (valor & ((1 << num_bits) - 1)) << bit_inicial;
  uint32_t maskOFF = (~valor & ((1 << num_bits) - 1)) << bit_inicial;
  IOSET = maskON;   // escribe los 1s
  IOCLR = maskOFF;  // escribe los 0s
}

void gpio_marcar_entrada(int bit_inicial, int num_bits) {
  uint32_t mask = ((1 << num_bits) - 1) << bit_inicial;
  IODIR = IODIR & ~mask;
}

void gpio_marcar_salida(int bit_inicial, int num_bits) {
  uint32_t mask = ((1 << num_bits) - 1) << bit_inicial;
  IODIR = IODIR | mask;
}

void test_gpio() {
  gpio_iniciar();
  gpio_marcar_salida(17, 9);
  gpio_marcar_entrada(17, 9);
  gpio_marcar_salida(6, 5);
  gpio_escribir(7, 3, 1);
  gpio_escribir(7, 3, 6);
  // Escribir algo en el gpio a partir del bit 17
  volatile int valor = gpio_leer(7, 3);
}
