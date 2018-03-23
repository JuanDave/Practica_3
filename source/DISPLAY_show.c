/*
 * DISPLAY_show.c
 *
 *  Created on: Feb 20, 2018
 *      Author: Josue
 */

#include "MKL25Z4.h"
#include "stdtypes.h"
#include "DISPLAY_show.h"
#include "stdint.h"
#include "DISPLAY_manager.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_pit.h"



uint32_t NumberMask [10] = {0x3F,0x6, 0x5B ,0x4F,0x66,0x6D, 0x7D, 0x7 ,0xFF, 0x67};

void DISPLAY_show_Getnumber(T_UFLOAT l_Value2Write) {
int dato=0;
//dato=l_Value2Write*100;
dato= l_Value2Write;
int unidades, decenas,centenas;

unidades = dato%10;
dato = dato-unidades;
decenas = (dato%100)/10;
dato =  dato-decenas;
centenas = dato/100;

}

void DISPLAY_show_ShowNumber(uint32_t index , T_ULONG l_transistor){
	uint32_t *maskIndex; /// POINTER MASKINDEX
	GPIO_ClearPinsOutput(GPIOC, ALL_REGISTER_MASK);  ///CLEAR DISPLA
	maskIndex=&NumberMask[index]; ///POINTS TO DIPLAY ARRAY
	GPIO_SetPinsOutput(GPIOC, *maskIndex);			 // SET DEFAULT
	GPIO_WritePinOutput(GPIOC,l_transistor,TRUE);
}

