#include "test_tableros.h"

void test_timer0(void);
void test_timer1(void);
void test_gpio(void);
void prototipo_planificador(void);

// MAIN
int main(void) {
  // test_tableros();

  // test_timer0();
  // test_timer1();
  //test_gpio();
  prototipo_planificador();

  // jugar
  // conecta4_jugar();

  while (1)
    ;  // no hay S.O., no se retorna
}
