#include "gestor_alarmas.h"

// Vector de alarmas
uint32_t alarmas[NUM_ALARMAS];
uint32_t tiempo[NUM_ALARMAS];


uint32_t ga_aux_data(uint8_t ID_msg, int esPeriodica, uint32_t retardo) {
    uint32_t aux_data = ID_msg << 24; //Los 8 bits más significativos son el msg asociado
    if (esPeriodica) { //Activar bit 23
        aux_data = aux_data | 0x800000;
    }
    aux_data = aux_data | (retardo & 0x7FFFFF);
    return aux_data;
}

uint32_t ga_retardo(uint32_t aux_data) {
    return aux_data & 0x7FFFFF;
}

int ga_es_periodica(uint32_t aux_data) {
    return (aux_data & 0x800000) != 0;
}

uint8_t ga_id_msg(uint32_t aux_data) {
    return aux_data >> 24;
}

void ga_programar_alarma(uint32_t aux_data) {
    //¿Qué pasa si excede el máximo de alarmas?
    for (int i = 0; i < NUM_ALARMAS; i++) {
        if (alarmas[i] == 0) {
            alarmas[i] = aux_data;
            tiempo[i] = ga_retardo(aux_data);
        }
        else if ((ga_id_msg(alarmas[i]) == ga_id_msg(aux_data))) {
            if (ga_retardo(aux_data) == 0) { //si retardo == 0
                alarmas[i] = 0; //cancelar
            }
            else {
                alarmas[i] = aux_data;
                tiempo[i] = ga_retardo(aux_data);
            }
        }
    }
}

void ga_comprobar_alarmas() {
    for (int i = 0; i < NUM_ALARMAS; i++) {
        if (alarmas[i] == 0 || --tiempo[i] > 0) continue;
        if (!ga_es_periodica(alarmas[i])) {
            alarmas[i] = 0; //cancelar
        }
        else {
            tiempo[i] = 0; //reset
        }
        //¿Tiene que poner algún mensaje especifico?
        cola_encolar_msg(ga_id_msg(alarmas[i]),0);
    }
}
/* ESTRUCTURA PLANIFICADOR
void kk() {

    temporizador_reloj(1);
    //for {
    evento_info evento = cola_desencolar_eventos();
    if (evento.ID_msg == Timer_Event) {
        ga_comprobar_alarmas(evento.veces);
    }
    msg_info msg = cola_desencolar_msg();
    if (msg.ID_msg == Set_Alarm) {
        ga_programar_alarma(msg.auxData);
    }
    
    //}
}
*/

