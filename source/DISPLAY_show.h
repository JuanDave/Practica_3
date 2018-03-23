/*
 * DISPLAY_show.h
 *
 *  Created on: Feb 20, 2018
 *      Author: Josue
 */
#include "stdint.h"
#ifndef DISPLAY_SHOW_H_
#define DISPLAY_SHOW_H_

#define ALL_REGISTER_MASK ((uint32_t)0xFFFFFFFF)

extern void DISPLAY_show_Getnumber(T_UFLOAT);
extern void DISPLAY_show_ShowNumber(uint32_t, T_ULONG);

#endif /* DISPLAY_SHOW_H_ */
