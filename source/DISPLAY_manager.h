/*
 * DISPLAY_manager.h
 *
 *  Created on: Feb 12, 2018
 *      Author: Josue
 */

#include "stdint.h"

#ifndef DISPLAY_MANAGER_H_
#define DISPLAY_MANAGER_H_

/// DISPLAY OUTPUT MACROS
#define LED_A_PIN_NUMBER ((uint32_t)0U)
#define LED_B_PIN_NUMBER ((uint32_t)1U)
#define LED_C_PIN_NUMBER ((uint32_t)2U)
#define LED_D_PIN_NUMBER ((uint32_t)3U)
#define LED_E_PIN_NUMBER ((uint32_t)4U)
#define LED_F_PIN_NUMBER ((uint32_t)5U)
#define LED_G_PIN_NUMBER ((uint32_t)6U)

// TRANSISTOR FOR MUX
#define TRANSISTOR_UNIDADES_NUMBER ((uint32_t)9U)
#define TRANSISTOR_DECENAS_NUMBER  ((uint32_t)10U)
#define TRANSISTOR_CENTENAS_NUMBER ((uint32_t)11U)

/// SENALAMIENTOS
#define SENALAMIENTO_CONTADOR ((uint32_t)12U)
#define SENALAMIENTO_TEMPORIZADOR ((uint32_t)13U)
#define SENALAMIENTO_ADC ((uint32_t)16U)

#define BUTTON_RESET_PIN_NUMBER 	 ((uint32_t)0U)
#define BUTTON_ASCENDENT_PIN_NUMBER  ((uint32_t)1U)
#define BUTTON_DESCENDENT_PIN_NUMBER ((uint32_t)2U)


extern void DISPLAY_manager_Output_Init(void);
extern void DISPLAY_manager_Input_Init(void);
extern T_UBYTE DISPLAY_manager_checkButtonReset();
extern uint32_t DISPLAY_manager_checkButtonAsc_Desc(uint32_t);
#endif /* DISPLAY_MANAGER_H_ */
