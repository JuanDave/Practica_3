/*
 * Init_pwm.c
 *
 *  Created on: Mar 14, 2018
 *      Author: Josue
 */

#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"
#include "Init_pwm.h"

	/*******************************************************************************
	 * Variables
	 ******************************************************************************/
	volatile bool brightnessUp = true; /* Indicate LED is brighter or dimmer */
	volatile uint8_t updatedDutycycle = 10U;

 	tpm_config_t tpmInfo;
    tpm_chnl_pwm_signal_param_t tpmParam;
    tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue;

void Init_pwm(){

    /* Configure tpm params with frequency 24kHZ */
    tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
    tpmParam.level = pwmLevel;
    tpmParam.dutyCyclePercent = updatedDutycycle;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
   /// BOARD_BootClockRUN();
   /// BOARD_InitDebugConsole();

    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);
    TPM_GetDefaultConfig(&tpmInfo);

    /* Initialize TPM module */
    TPM_Init(BOARD_TPM_BASEADDR, &tpmInfo);
    TPM_SetupPwm(BOARD_TPM_BASEADDR, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(BOARD_TPM_BASEADDR, kTPM_SystemClock);
}

void update_pwm(uint32_t AssignedData){
    /* Disable channel output before updating the dutycycle */
TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

/* Update PWM duty cycle */
TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,AssignedData);

/* Start channel output with updated dutycycle */
TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);

}
