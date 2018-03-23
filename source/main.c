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
#include "ADC_init.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "pin_mux.h"
#include "Init_pwm.h"

volatile bool pitIsrFlag = false;

void PIT_LED_HANDLER(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    pitIsrFlag = true;
}

typedef enum {RESET=0,NEXTSTATE}statesB;
typedef enum {ASC_DES_COUNTER=1,TIMER,ADC}estados;

T_UBYTE lub_selectorEstado();
T_UBYTE checkReset(T_UBYTE);
uint32_t Adc_dataHandler();
void despliegue(uint32_t);
uint32_t contador=0;

int main(void)
{
    DISPLAY_manager_Output_Init(); /// GPIO PORTC OUTPUT SETTINGS
    DISPLAY_manager_Input_Init();  ///GPIO PORTB  INPUT SETTINGS
    Init_pwm();
    Pit_Init_isr();
    ADC_Pin_init();
    ADC_init_channel();

uint32_t lsw_interruptCounter=0;
uint32_t secondCounter=0;
T_UBYTE state=ASC_DES_COUNTER;
uint32_t AssignedData =0;
uint32_t l_pwmLevel =0;
float l_Value2Write;
uint32_t lub_buttonPressedTime =0;
    while (true)
    {

      	if(GPIO_ReadPinInput(GPIOB, BUTTON_RESET_PIN_NUMBER)==FALSE){ ///CHECK RESET BUTTON
      		 if (true == pitIsrFlag){
      			lub_buttonPressedTime++;
      		 }
        	        	    				if(lub_buttonPressedTime>=2500){
        	        	    					lub_buttonPressedTime=0;
        	        	    					if(state>=3){
        	        	    						state=1;
        	        	    					}
        	        	    					else{
        	        	    						state++;
        	        	    						GPIO_WritePinOutput(GPIOC,SENALAMIENTO_CONTADOR,FALSE);
        	        	    						GPIO_WritePinOutput(GPIOC,SENALAMIENTO_TEMPORIZADOR,FALSE);
        	        	    						GPIO_WritePinOutput(GPIOC,SENALAMIENTO_ADC,FALSE);
        	        	    					}

        	        	    						}
        	        	    	else  {
        	        	    		AssignedData=0;
        	        	    		secondCounter=0;
        	        	    		}
        	        	    		}

        if (true == pitIsrFlag)
        {
        	switch(state){
            	case ASC_DES_COUNTER:
            		GPIO_WritePinOutput(GPIOC,SENALAMIENTO_CONTADOR,TRUE);
            		AssignedData=DISPLAY_manager_checkButtonAsc_Desc(AssignedData);
            		break;
            	case TIMER:
            		GPIO_WritePinOutput(GPIOC,SENALAMIENTO_TEMPORIZADOR,TRUE);
            		AssignedData=secondCounter;
            		break;
            	case ADC :
            		GPIO_WritePinOutput(GPIOC,SENALAMIENTO_ADC,TRUE);
            	if(lsw_interruptCounter==100){
            	AssignedData= ADC16_GetChannelConversionValue(ADC0, 0U);
               	l_Value2Write= (AssignedData*(3.3))/4096;
            	AssignedData=l_Value2Write*100;
                }
            		break;
            	default:
            		;
            		break;
            	}

        	  pitIsrFlag = false;

        	lsw_interruptCounter++;
        	contador++;

        	if(lsw_interruptCounter==1000){ //// 1000 miliseguncdos = 1 segundo
        		secondCounter++;            //// Aumenta la cuenta de segundos
        		lsw_interruptCounter=0;     ///  Reset bandera de interrupcion
        	}

        	if(secondCounter==101){			/// Despues de 100 , Reset a 0
        		secondCounter=0;
        	}

          despliegue(AssignedData);        //// Mostar datos en display

        	if(state==ADC){                  /// Si estado de ADC
           l_pwmLevel=AssignedData/3.3;
           update_pwm(l_pwmLevel);           /// Desplegar PWM  asi
        	}
        	else{                            /// En todos los demas casos
        		update_pwm(AssignedData);
        	}

        }
    }
}


void despliegue(uint32_t AssignedData){
	int unidades=0;
	int decenas=0;
	int centenas=0;
	uint32_t conversor =0;

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

}

