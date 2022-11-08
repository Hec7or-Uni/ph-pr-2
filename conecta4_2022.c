#include "conecta4_2022.h"

// devuelve ERROR en caso de no encontrar fila
uint8_t C4_calcular_fila(CELDA cuadricula[TAM_FILS][TAM_COLS],
                         uint8_t columna) {
  uint8_t fila = 1;  // row 0 is used to enumerate the columns

  if ((columna < 1) || (columna > NUM_COLUMNAS)) {
    return ERROR;
  }  // Out of the board. Columna must go form 1 to 7

  while ((fila <= NUM_FILAS) &&
         (celda_vacia(cuadricula[fila][columna]) == FALSE)) {
    fila++;
  }
  return fila <= NUM_FILAS ? fila : ERROR;
};

// devuelve la longitud de la línea más larga
__attribute__((noinline)) uint8_t conecta4_buscar_alineamiento_c(
    CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna,
    uint8_t color, int8_t delta_fila, int8_t delta_columna) {
  // avanzar hasta que cela esté vacía, sea distinto color o lleguemos al borde
  if (!C4_fila_valida(fila) || !C4_columna_valida(columna)) {
    return 0;
  }

  // posicion valida y mismo color
  if (celda_vacia(cuadricula[fila][columna]) ||
      (celda_color(cuadricula[fila][columna]) != color)) {
    return 0;
  }

  // avanzar índices
  uint8_t nueva_fila = fila + delta_fila;
  uint8_t nueva_columna = columna + delta_columna;

  // incrementar longitud y visitar celda vecina
  return 1 + conecta4_buscar_alineamiento_c(cuadricula, nueva_fila,
                                            nueva_columna, color, delta_fila,
                                            delta_columna);
}

// devuelve true si encuentra una línea de longitud mayor o igual a 4
__attribute__((noinline)) uint8_t conecta4_hay_linea_c_c(
    CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna,
    uint8_t color) {
  int8_t deltas_fila[4] = {0, -1, -1, 1};
  int8_t deltas_columna[4] = {-1, 0, -1, -1};
  unsigned int i = 0;
  uint8_t linea = FALSE;
  uint8_t long_linea = 0;

  // buscar linea en fila, columna y 2 diagonales
  for (i = 0; (i < 4) && (linea == FALSE); ++i) {
    // buscar sentido
    long_linea = conecta4_buscar_alineamiento_c(
        cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
    linea = long_linea >= 4;
    if (linea) {
      continue;
    }
    // buscar sentido inverso
    long_linea += conecta4_buscar_alineamiento_c(
        cuadricula, fila - deltas_fila[i], columna - deltas_columna[i], color,
        -deltas_fila[i], -deltas_columna[i]);
    linea = long_linea >= 4;
  }
  return linea;
}

uint8_t conecta4_hay_linea_arm_arm_c(CELDA cuadricula[TAM_FILS][TAM_COLS],
                                     uint8_t fila, uint8_t columna,
                                     uint8_t color) {
  int8_t deltas_fila[4] = {0, -1, -1, 1};
  int8_t deltas_columna[4] = {-1, 0, -1, -1};
  unsigned int i = 0;
  uint8_t long_linea = 0;
  uint8_t fila_aux = fila;
  uint8_t columna_aux = columna;

  if (!C4_fila_valida(fila) || !C4_columna_valida(columna) ||
      celda_vacia(cuadricula[fila][columna]) ||
      (celda_color(cuadricula[fila][columna]) != color)) {
    return FALSE;
  }

  // buscar linea en fila, columna y 2 diagonales
  for (i = 0; i < 4; ++i) {
    long_linea = 1;
    fila += deltas_fila[i];
    columna += deltas_columna[i];
    // buscar sentido
    while (!(!C4_fila_valida(fila) || !C4_columna_valida(columna) ||
             celda_vacia(cuadricula[fila][columna]) ||
             (celda_color(cuadricula[fila][columna]) != color))) {
      fila += deltas_fila[i];
      columna += deltas_columna[i];
      long_linea++;

      if (long_linea == 4) return TRUE;
    }

    fila = fila_aux - deltas_fila[i];
    columna = columna_aux - deltas_columna[i];
    // buscar sentido inverso
    while (!(!C4_fila_valida(fila) || !C4_columna_valida(columna) ||
             celda_vacia(cuadricula[fila][columna]) ||
             (celda_color(cuadricula[fila][columna]) != color))) {
      fila -= deltas_fila[i];
      columna -= deltas_columna[i];
      long_linea++;
      if (long_linea == 4) {
        return TRUE;
      }
    }
    fila = fila_aux;
    columna = columna_aux;
  }
  return FALSE;
}

// devuelve true si encuentra una línea de longitud mayor o igual a 4
__attribute__((noinline)) uint8_t conecta4_hay_linea_c_arm(
    CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna,
    uint8_t color) {
  int8_t deltas_fila[4] = {0, -1, -1, 1};
  int8_t deltas_columna[4] = {-1, 0, -1, -1};
  unsigned int i = 0;
  uint8_t linea = FALSE;
  uint8_t long_linea = 0;

  // buscar linea en fila, columna y 2 diagonales
  for (i = 0; (i < 4) && (linea == FALSE);
       ++i) {  // Cambiar el orden de la comprobación
    // buscar sentido
    long_linea = conecta4_buscar_alineamiento_arm(
        cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
    linea = long_linea >= 4;
    if (linea) {
      continue;  // return TRUE¿¿??;
    }
    // buscar sentido inverso
    long_linea += conecta4_buscar_alineamiento_arm(
        cuadricula, fila - deltas_fila[i], columna - deltas_columna[i], color,
        -deltas_fila[i], -deltas_columna[i]);
    linea = long_linea >= 4;
    // return condicional se podria?
  }
  return linea;
}

void C4_actualizar_tablero(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                           uint8_t columna, uint8_t val) {
  celda_poner_valor(&cuadricula[(fila)][(columna)], val);
}

// comprueba si esta jugada llena todo el tablero y hay empate
int C4_comprobar_empate(CELDA cuadricula[TAM_FILS][TAM_COLS]) {
  for (int i = 1; i < TAM_COLS; i++) {
    if (celda_vacia(cuadricula[TAM_FILS - 1][i])) {
      return FALSE;
    }
  }
  return TRUE;
}

int C4_verificar_4_en_linea(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
                            uint8_t columna, uint8_t color, int *fail) {
  uint8_t resultado_c_c =
      conecta4_hay_linea_c_c(cuadricula, fila, columna, color);
  uint8_t resultado_c_arm =
      conecta4_hay_linea_c_arm(cuadricula, fila, columna, color);
  uint8_t resultado_arm_c =
      conecta4_hay_linea_arm_c(cuadricula, fila, columna, color);
  uint8_t resultado_arm_arm =
      conecta4_hay_linea_arm_arm(cuadricula, fila, columna, color);
  if (fail != 0)
    *fail = resultado_c_c != resultado_c_arm ||
            resultado_c_c != resultado_arm_c ||
            resultado_c_c != resultado_arm_arm;
  return resultado_c_c && resultado_c_arm && resultado_arm_c &&
         resultado_arm_arm;
}

void conecta4_jugar(void) {
  // new, column, padding to prevent desalinating to 8 bytes
  static volatile uint8_t entrada[8] = {0, 0, 0, 0, 0, 0, 0, 0};

#include "tableros.h"

  uint8_t column, row, colour;
  colour = 1;  // empiezan jugador 1 (blancas)

  while (1) {
    while (entrada_nueva(entrada) == 0) {
    };
    column = entrada_leer(entrada);
    row =
        C4_calcular_fila(cuadricula_1, column);  // returns 0 if is not in range
    if (C4_fila_valida(row) && C4_columna_valida(column)) {
      C4_actualizar_tablero(cuadricula_1, row, column, colour);
      if (C4_verificar_4_en_linea(cuadricula_1, row, column, colour,
                                  0 /*NULL*/)) {
        while (1)
          ;
      }
      if (C4_comprobar_empate(cuadricula_1)) {
        while (1)
          ;
      }
      colour = C4_alternar_color(colour);
    }
    entrada_inicializar(entrada);
  }
}

void conecta4_sqs(evento_info evento) {
  switch (evento) {
    case PULSACION:
      if (evento.auxData == 2) break;
      break;
    case LATIDO:
      break;
    case PEDIR_VALOR:
      break;
    case DESACTIVAR_LATIDO:
      break;
    case ENCENDER_INVALIDO:
      break;
    case APAGAR_INVALIDO:
      break;
    case ENCENDER_DONE:
      break;
    case APAGAR_DONE:
      break;
    case CAMBIO_JUGADOR:
      break;
    case FIN; end(); break; case OVERFLOW:
      break;
  }
}