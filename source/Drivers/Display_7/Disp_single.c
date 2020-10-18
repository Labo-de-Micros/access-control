//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//	@file		Disp_single.c									//
//	@brief		Simple 7 segment display driver					//
//	@author		Grupo	4										//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//							Headers								//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "./Disp_single.h"
#include "../GPIO/gpio.h"
#include "../../board.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//		CONSTANT AND MACRO DEFINITIONS USING #DEFINE 			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define DISP_0		0x3F
#define DISP_1		0x06
#define DISP_2		0x5B
#define DISP_3		0x4F
#define DISP_4		0x66
#define DISP_5		0x6D
#define DISP_6		0x7D
#define DISP_7		0x07
#define DISP_8		0x7F
#define DISP_9		0x6F
#define DISP_CLEAR	0x00
#define DISP_A		0x77
#define DISP_B		0x7C
#define DISP_C		0x39
#define DISP_D		0x5E
#define DISP_E		0x79
#define DISP_F		0x71
#define DISP_G		0x3D
#define DISP_H		0x76
#define DISP_I		0x30
#define DISP_J		0x1E
#define DISP_K		0x75
#define DISP_L		0x38
#define DISP_M		0x15
#define DISP_N		0x37
#define DISP_O		0x3F
#define DISP_P		0x73
#define DISP_Q		0x6B
#define DISP_R		0x33
#define DISP_S		0x6D
#define DISP_T		0x78
#define DISP_U		0x3E
#define DISP_V		0x3E
#define DISP_W		0x2A
#define DISP_X		0x76
#define DISP_Y		0x6E
#define DISP_Z		0x5B
#define DISP_a		0x5F
#define DISP_b		0x7C
#define DISP_c		0x58
#define DISP_d		0x5E
#define DISP_e		0x7B
#define DISP_f		0x71
#define DISP_g		0x6F
#define DISP_h		0x74
#define DISP_i		0x10
#define DISP_j		0x0C
#define DISP_k		0x75
#define DISP_l		0x30
#define DISP_m		0x14
#define DISP_n		0x54
#define DISP_o		0x5C
#define DISP_p		0x73
#define DISP_q		0x67
#define DISP_r		0x50
#define DISP_s		0x6D
#define DISP_t		0x78
#define DISP_u		0x1C
#define DISP_v		0x1C
#define DISP_w		0x14
#define DISP_x		0x76
#define DISP_y		0x6E
#define DISP_z		0x5B
#define DISP_bar	0x80
#define DISP_END	0xFF

#define DISP_MASK 0x01

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//						STATIC VARIABLES						//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

static pin_t single_disp_pins[8];

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS W FILE LEVEL SCOPE//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

static uint8_t get_7_segments_char(char character);
/*****************************************************************
 * @brief: Return 7 segment binary value for the character.
 * @param character: A character to be converted.
 * **************************************************************/

static uint8_t get_7_segments_number(uint8_t num);
/*****************************************************************
 * @brief: Return 7 segment value for the number.
 * @param num: A number from 0-9 to be converted.
 * **************************************************************/

static void set_pins(uint8_t pins);
/*****************************************************************
 * @brief: Set the pins abcdefg HIGH or LOW depending on the pins parameter
 * @param pins: An 8 bit param indicating the state of the pins to be
 * 				displayed. (The most significant bit doesnt change anything.)
 * 				Ex:		pins = 01010111
 * 							g -> HIGH	1
 * 							f -> LOW	0
 * 							e -> HIGH	1
 * 							d -> LOW	0
 * 							c -> HIGH	1
 * 							b -> HIGH	1
 * 							a -> HIGH	1
 * **************************************************************/



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//					FUNCTION DEFINITIONS						//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void single_disp_init(void){
/*****************************************************************
 * @brief: Initialize the single display Driver
 * **************************************************************/
    static bool ya_init = false;
    if(ya_init)
        return;
    gpioMode(DISPLAY_PIN_A, OUTPUT);
    gpioMode(DISPLAY_PIN_B, OUTPUT);
    gpioMode(DISPLAY_PIN_C, OUTPUT);
    gpioMode(DISPLAY_PIN_D, OUTPUT);
    gpioMode(DISPLAY_PIN_E, OUTPUT);
    gpioMode(DISPLAY_PIN_F, OUTPUT);
    gpioMode(DISPLAY_PIN_G, OUTPUT);
    single_disp_pins[0] = DISPLAY_PIN_A;
    single_disp_pins[1] = DISPLAY_PIN_B;
    single_disp_pins[2] = DISPLAY_PIN_C;
    single_disp_pins[3] = DISPLAY_PIN_D;
    single_disp_pins[4] = DISPLAY_PIN_E;
    single_disp_pins[5] = DISPLAY_PIN_F;
    single_disp_pins[6] = DISPLAY_PIN_G;
    ya_init = true;
    return;
}

void single_disp_print(char letter){
/*****************************************************************
 * @brief: Prints a letter to the display
 * @param letter: letter to be printted.
 * **************************************************************/
    set_pins(get_7_segments_char(letter));
    return;
}

void single_disp_num(uint8_t num){
/*****************************************************************
 * @brief: Prints a number into the display
 * @param num: Number to be printed
 * **************************************************************/
    set_pins(get_7_segments_number(num));
    return;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//					LOCAL FUNCTION DEFINITIONS					//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

static uint8_t get_7_segments_char(char character){
/*****************************************************************
 * @brief: Return 7 segment binary value for the character.
 * @param character: A character to be converted.
 * **************************************************************/	
	uint8_t return_val = DISP_E;

	switch(character){
		case 'A':
			return_val = DISP_A;
			break;
		case 'a':
			return_val = DISP_a;
			break;
		case 'B':
			return_val = DISP_B;
			break;
		case 'b':
			return_val = DISP_b;
			break;
		case 'C':
			return_val = DISP_C;
			break;
		case 'c':
			return_val = DISP_c;
			break;
		case 'D':
			return_val = DISP_D;
			break;
		case 'd':
			return_val = DISP_d;
			break;
		case 'E':
			return_val = DISP_E;
			break;
		case 'e':
			return_val = DISP_e;
			break;
		case 'F':
			return_val = DISP_F;
			break;
		case 'f':
			return_val = DISP_f;
			break;
		case 'G':
			return_val = DISP_G;
			break;
		case 'g':
			return_val = DISP_g;
			break;
		case 'H':
			return_val = DISP_H;
			break;
		case 'h':
			return_val = DISP_h;
			break;
		case 'I':
			return_val = DISP_I;
			break;
		case 'i':
			return_val = DISP_i;
			break;
		case 'J':
			return_val = DISP_J;
			break;
		case 'j':
			return_val = DISP_j;
			break;
		case 'K':
			return_val = DISP_K;
			break;
		case 'k':
			return_val = DISP_k;
			break;
		case 'L':
			return_val = DISP_L;
			break;
		case 'l':
			return_val = DISP_l;
			break;
		case 'M':
			return_val = DISP_M;
			break;
		case 'm':
			return_val = DISP_m;
			break;
		case 'N':
			return_val = DISP_N;
			break;
		case 'n':
			return_val = DISP_n;
			break;
		case 'O':
			return_val = DISP_O;
			break;
		case 'o':
			return_val = DISP_o;
			break;
		case 'P':
			return_val = DISP_P;
			break;
		case 'p':
			return_val = DISP_p;
			break;
		case 'Q':
			return_val = DISP_Q;
			break;
		case 'q':
			return_val = DISP_q;
			break;
		case 'R':
			return_val = DISP_R;
			break;
		case 'r':
			return_val = DISP_r;
			break;
		case 'S':
			return_val = DISP_S;
			break;
		case 's':
			return_val = DISP_s;
			break;
		case 'T':
			return_val = DISP_T;
			break;
		case 't':
			return_val = DISP_t;
			break;
		case 'U':
			return_val = DISP_U;
			break;
		case 'u':
			return_val = DISP_u;
			break;
		case 'V':
			return_val = DISP_V;
			break;
		case 'v':
			return_val = DISP_v;
			break;
		case 'W':
			return_val = DISP_W;
			break;
		case 'w':
			return_val = DISP_w;
			break;
		case 'X':
			return_val = DISP_X;
			break;
		case 'x':
			return_val = DISP_x;
			break;
		case 'Y':
			return_val = DISP_Y;
			break;
		case 'y':
			return_val = DISP_y;
			break;
		case 'Z':
			return_val = DISP_Z;
			break;
		case 'z':
			return_val = DISP_z;
			break;
		case '-':
			return_val = DISP_bar;
			break;
		case ' ':
			return_val = DISP_CLEAR;
			break;
		case '\0':
			return_val = DISP_END;
			break;
			
		default:
			break;
	}	
	return return_val;
}

static uint8_t get_7_segments_number(uint8_t num){
/*****************************************************************
 * @brief: Return 7 segment value for the number.
 * @param num: A number from 0-9 to be converted.
 * **************************************************************/	
	uint8_t return_val;
	return_val = DISP_E;
	switch(num){
		case 0:
			return_val = DISP_0;
			break;
		case 1:
			return_val = DISP_1;
			break;
		case 2:
			return_val = DISP_2;
			break;
		case 3:
			return_val = DISP_3;
			break;
		case 4:
			return_val = DISP_4;
			break;
		case 5:
			return_val = DISP_5;
			break;
		case 6:
			return_val = DISP_6;
			break;
		case 7:
			return_val = DISP_7;
			break;
		case 8:
			return_val = DISP_8;
			break;
		case 9:
			return_val = DISP_9;
			break;
		case DISP_END:
			return_val=DISP_END;
			break;
		default:
			break;
	}
	return return_val;
}

static void set_pins(uint8_t pins){
/*****************************************************************
 * @brief: Set the pins abcdefg HIGH or LOW depending on the pins parameter
 * @param pins: An 8 bit param indicating the state of the pins to be
 * 				displayed. (The most significant bit doesnt change anything.)
 * 				Ex:		pins = 01010111
 * 							g -> HIGH	1
 * 							f -> LOW	0
 * 							e -> HIGH	1
 * 							d -> LOW	0
 * 							c -> HIGH	1
 * 							b -> HIGH	1
 * 							a -> HIGH	1
 * **************************************************************/
	if(pins==DISP_END) pins=DISP_CLEAR;
	for(uint8_t i = 0; i < 7; i++){	// Get the pins and starts shifting the mask
									// 00000001 i spaces left to OR and set the pin 
									// HIGH or LOW.
		if(((DISP_MASK << i) & pins) != 0x00)
			gpioWrite(single_disp_pins[i],HIGH);
		else
			gpioWrite(single_disp_pins[i],LOW);
	}
	return;
}