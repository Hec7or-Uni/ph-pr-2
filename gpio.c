/*
 IOPIN: para leer los de entrada
 IODIR: si el bit tiene un 0 es de entrada, y si tiene un 1 es de salida
 IOSET: 1s donde queremos poner 1s
 IOCLR: 1s donde queremos poner 0s
 */

void gpio_iniciar(void) {}

int gpio_leer(int bit_inicial, int num_bits) {}

void gpio_escribir(int bit_inicial, int num_bits, int valor) {}

void gpio_marcar_entrada(int bit_inicial, int num_bits) {}

void gpio_marcar_salida(int bit_inicial, int num_bits) {}
