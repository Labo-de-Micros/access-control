/////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////
 //	@file		PWM.h    									    //
 //	@brief		PWM driver. Advance Implementation		    	//
 //	@author		Grupo 4 										//
 /////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////

#ifndef _PWM_H_
#define _PWM_H_

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//							Headers								//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./Drivers/PWM/FTM.h"


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//		CONSTANT AND MACRO DEFINITIONS USING #DEFINE 		 	//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


#define PRESCALER 				32
#define SYS_CLOCK				50000000
#define PWM_MS_TO_TICKS(ms)		PWM_SEC_TO_TICKS((ms/1000.0))
#define PWM_SEC_TO_TICKS(s)		(s*SYS_CLOCK/PRESCALER)

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			FUNCTION PROTOTYPES WITH GLOBAL SCOPE				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


void set_DutyPWM(FTM_t ftm,FTMChannel_t Chn, uint16_t  percent);
/*****************************************************************
 * @brief set the PWM duty_cycle percentage
 * @param ftm FTM module to use
 * @param Chn channel of the FTM module to use
 * @param percent percentage of the Duty Cycle. Values between 1 and 99
 *****************************************************************/

void pwm_start_timer(uint16_t ticks,uint16_t duty_cycle,FTM_callback_t callback);

void PWM_Init(uint16_t modulos, FTM_Prescal_t prescaler,uint16_t duty);
//modulus en cantidad de tick totales para obtener el periodo
//prescaler en el enum definifo como FTM_PSC_XX


void PWM_ISR(void);