#include "conecta4_2022.h"
#include "entrada.h"
#include "temporizador.h"
#include "test_tableros.h"

void test_timer0(void);
// void test_timer1(void);
void test_gpio(void);

// MAIN
int main(void) {
  // inicializar sistema
  //... practica 2

  // test_tableros();

  // test_timer0();
  //  test_timer1();
  test_gpio();

  // jugar
  // conecta4_jugar();

  while (1)
    ;  // no hay S.O., no se retorna
}
