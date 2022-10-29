#ifndef GESTOR_ALARMAS_H
#define GESTOR_ALARMAS_H
#include <inttypes.h>
#include "utils.h"
#include "cola_msg.h"
#include "temporizador.h"

enum {
    NUM_ALARMAS = 8
};

/**
 * @brief 
 * @param ID_msg
 * @param esPeriodica
 * @param retardo
 * @return 
 */
uint32_t ga_aux_data(uint8_t ID_msg, int esPeriodica, uint32_t retardo);

/**
 * @brief 
 * @param alarma
 * @return
 */
uint32_t ga_retardo(uint32_t alarma);

/**
 * @brief 
 * @param alarma
 * @return
 */
int ga_es_periodica(uint32_t alarma);

/**
 * @brief 
 * @param alarma
 * @return
 */
uint8_t ga_id_msg(uint32_t alarma);

/**
 * @brief 
 * @param auxData
 */
void ga_programar_alarma(uint32_t aux_data);

/**
 * @brief 
 */
void ga_comprobar_alarmas(void);

/**
 * @brief 
 */
void ga_iniciar(void);

#endif
