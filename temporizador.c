#include "temporizador.h"

// para la memoria
// volatile uint32_t timer1_extra;
// void timer1_IRC(void) __irq
// {
// 	timer1_extra++;
// 	T1IR = 1;				 // Clear interrupt flag
// 	VICVectAddr = 0; // Acknowledge Interrupt
// }

void timer0_IRC(void) __irq;

void timer0_IRC(void) __irq {
  static int veces = 0;

  uint8_t evento = Timer_Event;
  cola_encolar_eventos(evento, ++veces, 0);
  T0TCR = T0TCR & ~0x1;  // detiene el contador
  T0PC = 0;
  T0TC = 0;
  T0IR = 1;         // Clear interrupt flag
  VICVectAddr = 0;  // Acknowledge Interrupt
}

void temporizador_iniciar() {
  // timer1_extra = 0;

  T1PR = 14;  // Cuenta cada microsegundo: 15 clk = 1 us (SE PONE 2 PORQUE ES 15
              // - 1) ;
  T1MR0 = UINT32_MAX;  // Por si queremos un dominio mayor, de varios miles de
                       // años en lugar de una hora

  T1MCR = 2;  // Reset on MR0
  // T1MCR = 3; // Interrumpe cada MR0 y reinicia el contador

  // contador a 0
  T1TCR = T1TCR & ~0x1;
  T1PC = 0;
  T1TC = 0;

  // No es necesario si solo se devuelve unint32_t
  // VICVectAddr1 = (unsigned long)timer1_IRC;
  // VICVectCntl1 = (VICVectCntl0 & 0x1ff)  | 0x25;
  // VICIntEnable = VICIntEnable | 0x00000020; // Enable Timer1 Interrupt.
}

void temporizador_empezar() {
  T1TCR = T1TCR | 0x1;  // comienza a contar
}

uint32_t temporizador_leer() {
  // Con 64 bits para microsegundos:
  // return ((uint64_t)timer1_extra << 32) + T1TC;
  // Con 32 bits:
  return T1TC;
}

uint32_t temporizador_parar() {
  uint32_t time = T1TC;
  T1TCR = T1TCR & ~0x1;  // detiene el contador
  T1PC = 0;
  T1TC = 0;
  return time;
}

void temporizador_reloj(int periodo) {
  T0PR = 14999;  // Cuenta cada milisegundo: 15 clk = 1 us;
  T0MR0 = periodo;

  T0MCR = 5;  // Interrumpe cada MR0 y para el contador

  VICVectAddr0 = (unsigned long)timer0_IRC;
  VICVectCntl0 = (VICVectCntl0 & 0x1ff) | 0x24;
  VICIntEnable = VICIntEnable | 0x00000010;  // Enable Timer0 Interrupt.

  // contador a 0
  T0TCR = T0TCR & ~0x1;
  T0PC = 0;
  T0TC = 0;
  T0TCR = T0TCR | 0x1;  // comienza a contar
}

void test_timer1(void) {
  volatile uint32_t time;
  temporizador_iniciar();
  volatile int kk = 123;
  kk += 12;
  time = kk;
  temporizador_empezar();
  time = temporizador_leer();
  while (1) {
    while ((time + (1000000 - 1)) > temporizador_leer())
      ;
    time = temporizador_leer();
  }
}

void test_timer0(void) {
  temporizador_reloj(5000);

  while (!cola_hay_eventos())
    ;

  while (1)
    ;
}
