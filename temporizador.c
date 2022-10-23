#include "temporizador.h"

volatile uint32_t timer1_extra;

void timer1_IRC(void) __irq {
	timer1_extra++;
	T1IR = 1;           // Clear interrupt flag
  VICVectAddr = 1;    // Acknowledge Interrupt
}	

void temporizador_iniciar()
{
	timer1_extra = 0;
	
	T1PR = 2;          // Cuenta cada microsegundo: 3 clk = 1 us (SE PONE 2 PORQUE ES 3 - 1) ;
  T1MR0 = UINT32_MAX; // Por si queremos un dominio mayor, de varios miles de años en lugar de una hora
	
  T1MCR = 3;          // Interrumpe cada MR0 y reinicia el contador
  T1TCR = 3;          // Habilita el contador y lo bloquea a 0 hasta llamar a la función temporizador_empezar
	
  VICVectAddr1 = (unsigned long)timer1_IRC;
  VICVectCntl1 = 0x20 | 5;
  VICIntEnable = VICIntEnable | 0x00000020; // Enable Timer1 Interrupt.
}

void temporizador_empezar()
{
  T1TCR = T1TCR & ~0x2; // detiene el reseteo del contador para comenzar a contar
}

uint32_t temporizador_leer()
{
	//Con 64 bits para microsegundos:
  //return ((uint64_t)timer1_extra << 32) + T1TC;
	//Con 32 bits:
	return T1TC;
}

uint32_t temporizador_parar()
{
  //T1TCR = T1TCR & ~0x2;
	return T1TC;
}

void temporizador_reloj(int periodo)
{
}

void test_timer(void) {
	volatile uint32_t time;
	temporizador_iniciar();
	volatile int kk =123;
	kk += 12;
	time = kk;
	temporizador_empezar();
	time = temporizador_leer();
	while (1) {
		while ((time + (1000000 - 1)) > temporizador_leer());
		time = temporizador_leer();
	}
}	
