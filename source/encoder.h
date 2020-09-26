//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//	@file		Encoder.h									    //
//	@brief		Encoder driver. 								//
//	@author		Grupo	4										//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


#ifndef _ENCODER_H_
#define _ENCODER_H_

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//							Headers								//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


#include <stdint.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//		CONSTANT AND MACRO DEFINITIONS USING #DEFINE 		 	//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define ENCODERS_MAX_CANT     1

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			ENUMERATIONS AND STRUCTURES AND TYPEDEFS			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

typedef uint8_t tim_id_t;
typedef void (*enc_callback_t)(void);

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			FUNCTION PROTOTYPES WITH GLOBAL SCOPE				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void encoder_init(void);
/*****************************************************************
 * @brief: Initialize the encoder Driver
 * **************************************************************/

void encoder_set_callback(enc_callback_t  ccw, enc_callback_t  cw,
    enc_callback_t  click, enc_callback_t double_click, enc_callback_t long_click);
/*****************************************************************
 * @brief: Set the callbacks corresponding to the different types
 *			of modes
 * @param ccw: Callback for Counter-Clockwise turn.
 * @param cw: Callback for Clockwise turn.
 * @param click: Callback for button pressed single time.
 * @param double_click: Callback for button pressed double time.
 * @param long_click: Callback for button long press.
 * **************************************************************/

#endif	// _ENCODER_H_