/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include "board.h"
#include "fsl_gpio.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "stdtypes.h"
#include "DISPLAY_manager.h"
#include "DISPLAY_show.h"
#include "fsl_debug_console.h"
#include "Pit_Init.h"
#include "fsl_pit.h"
#include "ADC_init.h"
#include "fsl_adc16.h"
#include "stdtypes.h"
#include "fsl_debug_console.h"
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

///void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool brightnessUp = true; /* Indicate LED is brighter or dimmer */
volatile uint8_t updatedDutycycle = 10U;
volatile uint8_t getCharValue = 0U;

volatile bool pitIsrFlag = false;

void PIT_LED_HANDLER(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    pitIsrFlag = true;
}

typedef enum {RESET=0,NEXTSTATE}statesB;
typedef enum {ASC_DES_COUNTER=1,TIMER,ADC}estados;

int main(void)
{
	 tpm_config_t tpmInfo;
	    tpm_chnl_pwm_signal_param_t tpmParam;
	    tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue;

	    /* Configure tpm params with frequency 24kHZ */
	    tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
	    tpmParam.level = pwmLevel;
	    tpmParam.dutyCyclePercent = updatedDutycycle;

	    /* Board pin, clock, debug console init */
	    BOARD_InitPins();
	    BOARD_BootClockRUN();
	    BOARD_InitDebugConsole();

	    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
	    CLOCK_SetTpmClock(1U);

	    TPM_GetDefaultConfig(&tpmInfo);
	    /* Initialize TPM module */
	    TPM_Init(BOARD_TPM_BASEADDR, &tpmInfo);

	    TPM_SetupPwm(BOARD_TPM_BASEADDR, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	    TPM_StartTimer(BOARD_TPM_BASEADDR, kTPM_SystemClock);

    DISPLAY_manager_Output_Init(); /// GPIO PORTC OUTPUT SETTINGS
    DISPLAY_manager_Input_Init();  ///GPIO PORTB  INPUT SETTINGS
    Pit_Init_isr();
    ADC_Pin_init();
    ADC_init_channel();


uint32_t contador=0;
uint32_t interruptCounter=0;
uint32_t secondCounter=0;
int unidades=0;
int decenas=0;
int centenas=0;
T_UBYTE l_opciones;
T_UBYTE state=ASC_DES_COUNTER;
uint32_t AssignedData =0;
uint32_t conversor =0;
///uint32_t contadorDeBounceAsc=0;
///uint32_t contadorDeBounceDesc=0;
uint32_t contadorDeBounceRes=0;
uint32_t tempo=0;
float l_Value2Write;
uint32_t adc_flag=0;
    while (true)
    {

        /* Check whether occur interupt and toggle LED */
        if (true == pitIsrFlag)
        {

        	if(GPIO_ReadPinInput(GPIOB, BUTTON_RESET_PIN_NUMBER)==FALSE){ ///CHECK RESET BUTTON
        	    				if(contadorDeBounceRes>=500){
        	    					contadorDeBounceRes=0;
        	    					if(state==3){
        	    						state=1;
        	    					}
        	    					else{
        	    						state++;
        	    					}
        	    					//AssignedData=1;
        	    						}
        	    	else {  		contadorDeBounceRes++;
        	    					}
        	    			}

        	/*while(GPIO_ReadPinInput(GPIOB, BUTTON_RESET_PIN_NUMBER)==FALSE){
                tempo++;
                if(tempo>5000){
                	AssignedData=2;
                	tempo=0;
                }
                	}*/


        	    	switch(state){
        	        	case ASC_DES_COUNTER:
        	        		AssignedData=DISPLAY_manager_checkButtonAsc_Desc(AssignedData);
        	        		break;
        	        	case TIMER:
        	        		AssignedData=secondCounter;
        	        		break;
        	        	case ADC :
if(interruptCounter==500){
		adc_flag=1;
        	        	AssignedData= ADC16_GetChannelConversionValue(ADC0, 0U);
        	           	l_Value2Write= (AssignedData*(3.3))/4096;
        	        	AssignedData=l_Value2Write*100;
}
        	        	        //AssignedData=ADC16_GetChannelConversionValue(ADC0, 0U);
        	        		break;
        	        	default:
        	        		AssignedData=DISPLAY_manager_checkButtonAsc_Desc(AssignedData);
        	        		break;
        	        	}

        	interruptCounter++;
        	contador++;
        	if(interruptCounter==1000){
        		secondCounter++;  ///Cuenta cada segundo
        	  interruptCounter=0;
        	}

        	if(secondCounter==101){
        		secondCounter=0;
        	}

///            PRINTF("\r\n Channel No.0 interrupt is occured !");
           /// LED_TOGGLE();
            pitIsrFlag = false;

            conversor=AssignedData;
            unidades = conversor%10;
            conversor = conversor-unidades;
            decenas = (conversor%100)/10;
            conversor =  conversor-decenas;
            centenas = conversor/100;

        	if(contador==4){
        		DISPLAY_show_ShowNumber(unidades,TRANSISTOR_UNIDADES_NUMBER);
        	}
        	if(contador==8){
        		DISPLAY_show_ShowNumber(decenas,TRANSISTOR_DECENAS_NUMBER);
        	}
        	if(contador==12){
        		DISPLAY_show_ShowNumber(centenas,TRANSISTOR_CENTENAS_NUMBER);
        		contador=0;
        	}
        	/* Disable channel output before updating the dutycycle */


        	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

        	if(adc_flag==1){
        		adc_flag=0;
        		AssignedData=AssignedData;
		        /* Update PWM duty cycle */
TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
	        		        		AssignedData);
        	}
        	else{
        	        	        		        /* Update PWM duty cycle */
        	TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
        	        	        		        		AssignedData);
        	}
        	  /* Start channel output with updated dutycycle */
        	 TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);

        }
    }
}

