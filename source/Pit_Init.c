/*
 * Pit_Init.c
 *
 *  Created on: Feb 22, 2018
 *      Author: Josue
 */
#include "Pit_Init.h"

void Pit_Init_isr(void ){
    /* Structure of initialize PIT */
    pit_config_t pitConfig;

    /* Initialize and enable LED */
   /// LED_INIT();
    /*
         * pitConfig.enableRunInDebug = false;
         */
        PIT_GetDefaultConfig(&pitConfig);

        /* Init pit module */
        PIT_Init(PIT, &pitConfig);

        /* Set timer period for channel 0 */
        PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000U, PIT_SOURCE_CLOCK));

        /* Enable timer interrupts for channel 0 */
        PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

        /* Enable at the NVIC */
        EnableIRQ(PIT_IRQ_ID);

        /* Start channel 0 */
        PRINTF("\r\nStarting channel No.0 ...");
        PIT_StartTimer(PIT, kPIT_Chnl_0);
}
