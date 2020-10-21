/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//	@file		PWM.h    									   //
//	@brief		PWM driver. Advance Implementation		       //
//	@author		Grupo 4 									   //
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

#ifndef _PWM_H
#define _PWM_H

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//							Headers								//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//		CONSTANT AND MACRO DEFINITIONS USING #DEFINE 		 	//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


#define PRESCALER 				32      //Factor de division del SYS_CLOCK
#define SYS_CLOCK				50000000
#define PWM_MS_TO_TICKS(ms)		PWM_SEC_TO_TICKS((ms/1000.0))
#define PWM_SEC_TO_TICKS(s)		(s*SYS_CLOCK/PRESCALER)

#if (PRESCALER != 32)
#error Beware! Prescaler configured wrong in pwm_init()!
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			ENUMERATIONS AND STRUCTURES AND TYPEDEFS			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

typedef void (*PWM_callback_t)(void);

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			FUNCTION PROTOTYPES WITH GLOBAL SCOPE				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void pwm_init(uint16_t modulus);
/*****************************************************************
 * @brief: Funcion para inicializar el modulo PWM, esta inicializa
 *          internamente el modulo de FTM.
 * @param modulus: Cantidad de ticks totales para obtener el periodo
 *****************************************************************/

void pwm_start_timer(uint16_t ticks,PWM_callback_t call);
/*****************************************************************
 * @brief: Utilizando el modulo de PWM para generar un timer preciso
 * 			sin la utilizacion de Systick(muy eficiente ya que no consume
 * 			recursos del procesador realizando pooling periodicamente)
 * @param ticks: Ticks que debe contar hasta finalizar e interrumpir.
 * 				Los ticks deben ser calculados de manera que:
 * 				Ticks = time * SYS_CLOCK / PreScaler
 * 				donde time es el tiempo en segundos.
 * @param call: callback to be called whe the amount of ticks are finished.
 *****************************************************************/

#endif  //_PWM_H
