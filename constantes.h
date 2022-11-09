#ifndef CONSTANTES_H
#define CONSTANTES_H

enum Eventos { 
  TEMPORIZADOR,
  PULSACION,
	OVERFLOW_E
};

enum Mensajes {
	INICIO,
  SET_ALARM,
  RESET_1,
  RESET_2,
  POWER_DOWN,
	
  LATIDO,
	APAGAR_LATIDO,
	JUGADOR,          //auxData := turno
	LEER_ENTRADA,     //mensaje periodico
	VALIDAR_ENTRADA,  //pregunta al juego
	ENTRADA_VALIDADA, //respuesta del juego
	JUGADA_REALIZADA,
	APAGAR_REALIZADA,
	
  FIN,
	OVERFLOW_M
};

#endif
