#include "power.h"

void power_down() {
	EXTWAKE = 6;
  PCON = PCON | 0x2;
}

void idle() { PCON = PCON | 0x1; }
