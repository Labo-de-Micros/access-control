//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//	@file		Display.h	    								//
//	@brief	    Display Screen Driver           				//
//	@author		Grupo	4										//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#ifndef _DISPLAY_H
#define _DISPLAY_H

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

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			ENUMERATIONS AND STRUCTURES AND TYPEDEFS			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			FUNCTION PROTOTYPES WITH GLOBAL SCOPE				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void display_init(void);
/*****************************************************************
 * @brief: Initialize the Display Screen Driver
 * **************************************************************/

void display_set_string(char * string);
/*****************************************************************
 * @brief: Set a string on the screen diplay
 * @param string: String to be printed on the display.
 * **************************************************************/

void display_set_number(uint16_t number);
/*****************************************************************
 * @brief: Prints a number into the display Screen
 * @param number: Number to be printed.
 * **************************************************************/

void display_updater(void);
/*****************************************************************
 * @brief: Updates the internal Finate State Machine of the Screen
 *          Display. It is important to run this function periodically.
 * **************************************************************/

#endif  //_DISPLAY_H