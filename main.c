#include "conecta4_2022.h"
#include "entrada.h"
#include "temporizador.h"
#include "test_tableros.h"

void test_timer0(void);
void test_timer1(void);
void test_gpio(void);
void prototipo_planificador(void);

// MAIN
int main(void) {
  // inicializar sistema
  //... practica 2

  // test_tableros();
	volatile uint32_t in = 0x20, out = 0;
	//CLZ(in,out);
	out = MSB(in);

  // test_timer0();
  // test_timer1();
  // test_gpio();
  prototipo_planificador();

  // jugar
  // conecta4_jugar();

  while (1)
    ;  // no hay S.O., no se retorna
}
