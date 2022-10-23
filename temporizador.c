#include "temporizador.h"

void temporizador_iniciar()
{

  // 3000clk = 1us ; 30000clk = 1ms

  // configuration of Timer 1
  T1MR0 = 149999; // 10mSec = 15.000-1 counts
  T1MCR = 3;      // Interrumpe cada MR0 y reinicia el contador
  T1TCR = 3;      // Habilita el contador y lo bloquea a 0 hasta llamar a la función temporizador_empezar
  // configuration of the IRQ slot number 1 of the VIC for Timer 0 Interrupt
  VICVectAddr1 = (unsigned long)tc1; // set interrupt vector in 0
  // 0x20 bit 5 enables vectored IRQs.
  // 5 is the number of the interrupt assigned. Number 5 is the Timer 1 (see table 40 of the LPC2105 user manual
  VICVectCntl1 = 0x20 | 5;
  VICIntEnable = VICIntEnable | 0x00000020; // Enable Timer1 Interrupt.
}

void temporizador_empezar()
{
  T1TCR = T1TCR & ~0x2; // detiene el reseteo del contador para comenzar a contar
}

uint32_t temporizador_leer()
{
  return uint64_t(T1TC) << 32 + T1PC;         // en clks
  return uint64_t(T1TC) << m - n + T1PC >> n; // en clks
  // return T1TC % 63;
}

uint32_t temporizador_parar()
{
  T1TCR = T1TCR & ~0x2;
}

void temporizador_reloj(int periodo)
{
}