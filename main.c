#include "conecta4_2022.h"
#include "entrada.h"
#include "test_tableros.h"
#include "temporizador.h"


void test_timer(void);

// MAIN
int main(void)
{
	// inicializar sistema
	//... practica 2

	//test_tableros();
	
	test_timer();
	
	// jugar
	//conecta4_jugar();

	while (1)
		; // no hay S.O., no se retorna
}
