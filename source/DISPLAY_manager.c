/*
 * DISPLAY_manager.c
 *
 *  Created on: Feb 12, 2018
 *      Author: Josue
 */
#include "MKL25Z4.h"
#include "stdtypes.h"
#include "DISPLAY_manager.h"
#include "stdint.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"



/*T_WORD contadorDeBounceRes=0;
	T_UBYTE DISPLAY_manager_checkButtonReset(){

		if(GPIO_ReadPinInput(GPIOB, BUTTON_RESET_PIN_NUMBER)==FALSE){ ///CHECK RESET BUTTON
			if(contadorDeBounceRes>=2000){
				contadorDeBounceRes=0;
				return 1;
					}
else {  		contadorDeBounceRes++;
				}
		}
		return 2;
	}*/


uint32_t contadorDeBounceAsc=0;
uint32_t contadorDeBounceDesc=0;
uint32_t DISPLAY_manager_checkButtonAsc_Desc(uint32_t valor){
	uint32_t a=valor;
			if(GPIO_ReadPinInput(GPIOB, BUTTON_ASCENDENT_PIN_NUMBER)==FALSE){ //CHECK ASCENDENT BUTTON
					if(contadorDeBounceAsc>=500){
						contadorDeBounceAsc=0;
						if(a==100){
						   	    a=0;
						   	    		}
						   	    		else{
						   	    		a++;
						   	    		}
							}
						else {  		contadorDeBounceAsc++;
						}
						}

						if(GPIO_ReadPinInput(GPIOB, BUTTON_DESCENDENT_PIN_NUMBER)==FALSE){ //CHECK DESCENDENT BUTTON
						if(contadorDeBounceDesc>=500){
						contadorDeBounceDesc=0;
						if(a==0){
							a=100;
						}
						else{
						a--;
						}
							}
						else {  		contadorDeBounceDesc++;
														}
										}
		return a;
		}




void ADC_Pin_init(void){
	CLOCK_EnableClock(kCLOCK_PortE);
	PORT_SetPinMux(PORTE, 20, kPORT_PinDisabledOrAnalog); /* PORTE20 (pin 13) is configured as ADC0_DP0 */
}


extern void DISPLAY_manager_Input_Init(void){
	///PORTB Clock Source Enable
	CLOCK_EnableClock(kCLOCK_PortB);
// SET PINS AS GPIO'S STRUCTURES
	port_pin_config_t  ls_ButtonReset_PinGPIO , ls_ButtonAsc_PinGPIO ,ls_ButtonDes_PinGPIO;
	// SET AS GPIO
	ls_ButtonReset_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_ButtonAsc_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_ButtonDes_PinGPIO.mux=kPORT_MuxAsGpio;

	//PIN CONFIGURATION
	PORT_SetPinConfig(PORTB,BUTTON_RESET_PIN_NUMBER,&ls_ButtonReset_PinGPIO);//BUTTON RESET
	PORT_SetPinConfig(PORTB,BUTTON_ASCENDENT_PIN_NUMBER,&ls_ButtonAsc_PinGPIO);//BUTTON ASCENDENT
	PORT_SetPinConfig(PORTB,BUTTON_DESCENDENT_PIN_NUMBER,&ls_ButtonDes_PinGPIO);//BUTTON DESCENDENT

	//PIN INITIALIZATION
		//Pin Config Structures //Local Variables
		gpio_pin_config_t ls_ButtonReset_PinCfg ,ls_ButtonAsc_PinCfg,ls_ButtonDes_PinCfg;

		/// Pin As Outputs
		ls_ButtonReset_PinCfg.pinDirection=kGPIO_DigitalInput;
		ls_ButtonAsc_PinCfg.pinDirection=kGPIO_DigitalInput;
		ls_ButtonDes_PinCfg.pinDirection=kGPIO_DigitalInput;

		GPIO_PinInit(GPIOB, BUTTON_RESET_PIN_NUMBER,&ls_ButtonReset_PinCfg);//BUTTON RESET
		GPIO_PinInit(GPIOB, BUTTON_ASCENDENT_PIN_NUMBER,&ls_ButtonAsc_PinCfg);// BUTTON ASCENDENT
		GPIO_PinInit(GPIOB, BUTTON_DESCENDENT_PIN_NUMBER,&ls_ButtonDes_PinCfg);// BUTTON DESCENDENT

		///STRUSCTURES FOR INPUT CONFIGURATION
		port_pin_config_t ls_ButtonReset_PortCfg , ls_ButtonAsc_PortCfg,ls_ButtonDes_PortCfg;
		//INPUTS WITH PULL-UPS
		ls_ButtonReset_PortCfg.pullSelect=kPORT_PullUp;
		ls_ButtonAsc_PortCfg.pullSelect=kPORT_PullUp;
		ls_ButtonDes_PortCfg.pullSelect=kPORT_PullUp;

		PORT_SetPinConfig(PORTB,BUTTON_RESET_PIN_NUMBER,&ls_ButtonReset_PortCfg );
		PORT_SetPinConfig(PORTB,BUTTON_ASCENDENT_PIN_NUMBER,&ls_ButtonAsc_PortCfg );
		PORT_SetPinConfig(PORTB,BUTTON_DESCENDENT_PIN_NUMBER,&ls_ButtonDes_PortCfg );

	return;
}


void DISPLAY_manager_Output_Init(void){
	///PORTC Clock Source Enable
	CLOCK_EnableClock(kCLOCK_PortC);

	//SET PINS AS GPIO'S STRUCTURES
	port_pin_config_t  ls_LedA_PinGPIO ,ls_LedB_PinGPIO,ls_LedC_PinGPIO,ls_LedD_PinGPIO,ls_LedE_PinGPIO,ls_LedF_PinGPIO,ls_LedG_PinGPIO;
	// SET AS GPIO

	///OUTPUTS FOR MULTIPLEX
	port_pin_config_t ls_Transistor_unidades,ls_Transistor_decenas,ls_Transistor_centenas;

	ls_LedA_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_LedB_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_LedC_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_LedD_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_LedE_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_LedF_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_LedG_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_Transistor_unidades.mux=kPORT_MuxAsGpio;
	ls_Transistor_decenas.mux=kPORT_MuxAsGpio;
	ls_Transistor_centenas.mux=kPORT_MuxAsGpio;

	//PIN CONFIGURATION
	PORT_SetPinConfig(PORTC,LED_A_PIN_NUMBER,&ls_LedA_PinGPIO);//LED A
	PORT_SetPinConfig(PORTC,LED_B_PIN_NUMBER,&ls_LedB_PinGPIO);//LED B
	PORT_SetPinConfig(PORTC,LED_C_PIN_NUMBER,&ls_LedC_PinGPIO);//LED C
	PORT_SetPinConfig(PORTC,LED_D_PIN_NUMBER,&ls_LedD_PinGPIO);//LED D
	PORT_SetPinConfig(PORTC,LED_E_PIN_NUMBER,&ls_LedE_PinGPIO);//LED E
	PORT_SetPinConfig(PORTC,LED_F_PIN_NUMBER,&ls_LedF_PinGPIO);//LED F
	PORT_SetPinConfig(PORTC,LED_G_PIN_NUMBER,&ls_LedG_PinGPIO);//LED G

	// Transis -mux configuration
	PORT_SetPinConfig(PORTC,TRANSISTOR_UNIDADES_NUMBER,&ls_LedG_PinGPIO);//Transistor Unidades
	PORT_SetPinConfig(PORTC,TRANSISTOR_DECENAS_NUMBER,&ls_LedG_PinGPIO);//Transistor Decenas
	PORT_SetPinConfig(PORTC,TRANSISTOR_CENTENAS_NUMBER,&ls_LedG_PinGPIO);//Transistor Centenas


	//PIN INITIALIZATION
	//Pin Config Structures //Local Variables
	gpio_pin_config_t ls_LedA_PinCfg ,ls_LedB_PinCfg,ls_LedC_PinCfg,ls_LedD_PinCfg,ls_LedE_PinCfg,ls_LedF_PinCfg,ls_LedG_PinCfg;

	//Pin Config Structures //Local Variables TRANSISTOR MUX
	gpio_pin_config_t ls_TRANSISTOR_unidadesCfg ,ls_TRANSISTOR_decenasCfg,ls_TRANSISTOR_centenasCfg;

	/// Pin As Outputs DISPLAY
	ls_LedA_PinCfg.pinDirection=kGPIO_DigitalOutput;
	ls_LedB_PinCfg.pinDirection=kGPIO_DigitalOutput;
	ls_LedC_PinCfg.pinDirection=kGPIO_DigitalOutput;
	ls_LedD_PinCfg.pinDirection=kGPIO_DigitalOutput;
	ls_LedE_PinCfg.pinDirection=kGPIO_DigitalOutput;
	ls_LedF_PinCfg.pinDirection=kGPIO_DigitalOutput;
	ls_LedG_PinCfg.pinDirection=kGPIO_DigitalOutput;

	//Pin As outputs -transistor mux
	ls_TRANSISTOR_unidadesCfg.pinDirection=kGPIO_DigitalOutput;
	ls_TRANSISTOR_decenasCfg.pinDirection=kGPIO_DigitalOutput;
	ls_TRANSISTOR_centenasCfg.pinDirection=kGPIO_DigitalOutput;
    /// MUX LOGIC OUTPUT
	ls_TRANSISTOR_unidadesCfg.outputLogic= FALSE;
	ls_TRANSISTOR_decenasCfg.outputLogic= FALSE;
	ls_TRANSISTOR_centenasCfg.outputLogic= FALSE;


	ls_LedA_PinCfg.outputLogic= TRUE;
	ls_LedB_PinCfg.outputLogic= TRUE;
	ls_LedC_PinCfg.outputLogic= TRUE;
	ls_LedD_PinCfg.outputLogic= TRUE;
	ls_LedE_PinCfg.outputLogic= TRUE;
	ls_LedF_PinCfg.outputLogic= TRUE;
	ls_LedG_PinCfg.outputLogic= TRUE;

	/// DISPLAY INIT
	GPIO_PinInit(GPIOC, LED_A_PIN_NUMBER,&ls_LedA_PinCfg);//SALIDA A
	GPIO_PinInit(GPIOC, LED_B_PIN_NUMBER,&ls_LedB_PinCfg);//SALIDA B
	GPIO_PinInit(GPIOC, LED_C_PIN_NUMBER,&ls_LedC_PinCfg);//SALIDA C
	GPIO_PinInit(GPIOC, LED_D_PIN_NUMBER,&ls_LedD_PinCfg);//SALIDA D
	GPIO_PinInit(GPIOC, LED_E_PIN_NUMBER,&ls_LedE_PinCfg);//SALIDA E
	GPIO_PinInit(GPIOC, LED_F_PIN_NUMBER,&ls_LedF_PinCfg);//SALIDA F
	GPIO_PinInit(GPIOC, LED_G_PIN_NUMBER,&ls_LedG_PinCfg);//SALIDA G

	//TRANSISTOR MUX INIT
	GPIO_PinInit(GPIOC, TRANSISTOR_UNIDADES_NUMBER,&ls_TRANSISTOR_unidadesCfg);//SALIDA E
	GPIO_PinInit(GPIOC, TRANSISTOR_DECENAS_NUMBER,&ls_TRANSISTOR_decenasCfg);//SALIDA F
	GPIO_PinInit(GPIOC, TRANSISTOR_CENTENAS_NUMBER,&ls_TRANSISTOR_centenasCfg);//SALIDA G

	return;
}
