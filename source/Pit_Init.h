/*
 * Pit_Init.h
 *
 *  Created on: Feb 22, 2018
 *      Author: Josue
 */

#ifndef PIT_INIT_H_
#define PIT_INIT_H_

/*******************************************************************************/
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_pit.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PIT_LED_HANDLER PIT_IRQHandler
#define PIT_IRQ_ID PIT_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()

extern void Pit_Init_isr(void);


#endif /* PIT_INIT_H_ */
