//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//	@file		Screen.h										//
//	@brief		4 seven segment display screen services.		//
//	@author		Grupo	4										//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#ifndef _SCREEN_H
#define _SCREEN_H

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//							Headers								//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Display_7.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//		CONSTANT AND MACRO DEFINITIONS USING #DEFINE 		 	//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define SCREEN_MAX_AMOUNT  1

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			ENUMERATIONS AND STRUCTURES AND TYPEDEFS			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

typedef uint8_t screen_id_t;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			FUNCTION PROTOTYPES WITH GLOBAL SCOPE				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void initScreen(void);
/*****************************************************************
 * @brief: Initialize the Seven segment screen driver
 * **************************************************************/



void display_number(uint8_t num);
/*****************************************************************
 * @brief: Set a specified number on the screen of the seven segment display
 * @param num: A number from 0-9999 to be displayed on the screen.
 * **************************************************************/

void display_text(char * stream);
/*****************************************************************
 * @brief: Set a specified number on the screen of the seven segment display
 * @param stream: A char stream to be displayed on the screen.
 * **************************************************************/

void clear_display(void);
/*****************************************************************
 * @brief: Clears the screen (nothing will be displayed).
 * **************************************************************/

#endif