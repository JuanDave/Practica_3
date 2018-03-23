/*
 * Init_pwm.h
 *
 *  Created on: Mar 14, 2018
 *      Author: Josue
 */

#ifndef INIT_PWM_H_
#define INIT_PWM_H_

#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"

#define BOARD_TPM_BASEADDR TPM2
#define BOARD_TPM_CHANNEL 1U

/* Interrupt to enable and flag to read; depends on the TPM channel used */
#define TPM_CHANNEL_INTERRUPT_ENABLE kTPM_Chnl1InterruptEnable
#define TPM_CHANNEL_FLAG kTPM_Chnl1Flag

/* Interrupt number and interrupt handler for the TPM instance used */
#define TPM_INTERRUPT_NUMBER TPM2_IRQn
#define TPM_LED_HANDLER TPM2_IRQHandler

/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)


extern void Init_pwm();
extern void update_pwm();


#endif /* INIT_PWM_H_ */
