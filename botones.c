#include "botones.h"

/*
 PINSEL0:
 PINSEL1:
 */

void boton1_IRC(void) __irq {
  static int veces1 = 0;

  VICIntEnClr = 0x00008000;  // deshabilita eint1
  EXTINT = EXTINT | 0x2;     // borra el flag de interrupcion
  VICVectAddr = 0;           // Acknowledge Interrupt

  cola_encolar_eventos(Pulsacion, ++veces1, 1);
  cola_encolar_msg(Set_Alarm, ga_aux_data(Reset1, TRUE, 10));
}

void boton2_IRC(void) __irq {
  static int veces2 = 0;

  VICIntEnClr = 0x00010000;  // deshabilita eint2
  EXTINT = EXTINT | 0x4;     // borra el flag de interrupcion
  VICVectAddr = 0;           // Acknowledge Interrupt

  cola_encolar_eventos(Pulsacion, ++veces2, 2);
  cola_encolar_msg(Set_Alarm, ga_aux_data(Reset2, TRUE, 10));
}

void botones_iniciar(void) {
  PINSEL0 = PINSEL0 | ((uint32_t)0xA << 28);  // 10 10 ...

  VICVectAddr1 = (unsigned long)boton1_IRC;
  // bit 5 enable
  // bits 4:0 son el indice del dispositivo EINT1 (15)
  VICVectCntl1 = (VICVectCntl1 & ~0x1f) | 0x2F;

  VICVectAddr2 = (unsigned long)boton2_IRC;
  // bit 5 enable
  // bits 4:0 son el indice del dispositivo EINT2 (16)
  VICVectCntl2 = (VICVectCntl2 & ~0x1f) | 0x30;

  VICIntEnable = VICIntEnable | 0x18000;  // Enable EINT[1,2] Interrupt.
}

void boton1_reset(void) {
  EXTINT = EXTINT | 0x2;                     // borra el flag de interrupcion
  VICIntEnable = VICIntEnable | 0x00008000;  // Enable EINT1 Interrupt.
}

void boton2_reset(void) {
  EXTINT = EXTINT | 0x4;                     // borra el flag de interrupcion
  VICIntEnable = VICIntEnable | 0x00010000;  // Enable EINT2 Interrupt.
}

int boton1_pulsado() {
  EXTINT = EXTINT | 0x2;  // borra el flag de interrupcion
  // si aqui se vuelve a activar entonces el boton está pulsado
  return (EXTINT & 0x2) != 0;
}

int boton2_pulsado() {
  EXTINT = EXTINT | 0x4;  // borra el flag de interrupcion
  // si aqui se vuelve a activar entonces el boton está pulsado
  return (EXTINT & 0x4) != 0;
}
