//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//	@file		Encoder.c										//
//	@brief		Encoder driver. Advance Implementation			//
//	@author		Grupo	4										//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//							Headers								//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <stddef.h>
#include "encoder.h"
#include "gpio.h"
#include "board.h"
#include "timer.h"
#include "button.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//		CONSTANT AND MACRO DEFINITIONS USING #DEFINE 			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define ENCODER_TIME_TIMER	1

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			ENUMERATIONS AND STRUCTURES AND TYPEDEFS	  		//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

typedef enum{
	ENCODER_IDLE_ST,

	ENCODER_CASE_1_0_ST,
	ENCODER_CASE_1_1_ST,
	ENCODER_CASE_1_2_ST,
	ENCODER_CASE_1_3_ST,

	ENCODER_CASE_2_0_ST,
	ENCODER_CASE_2_1_ST,
	ENCODER_CASE_2_2_ST,
	ENCODER_CASE_2_3_ST,

	ENCODER_ERROR_ST
}encoder_states_t;

typedef enum{
	ENCODER_B_NEGATIVE_EDGE_EV,
	ENCODER_B_POSITIVE_EDGE_EV,
	ENCODER_A_NEGATIVE_EDGE_EV,
	ENCODER_A_POSITIVE_EDGE_EV,
	ENCODER_TIMER_FINISHED_EV,
	ENCODER_NO_EV
}encoder_events_t;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//						STATIC VARIABLES						//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

static tim_id_t encoder_timer;
static button_id_t encoder_button;
enc_callback_t  callback_ccw;
enc_callback_t  callback_cw;
enc_callback_t  callback_click;
enc_callback_t  callback_double;
enc_callback_t  callback_long;
static encoder_states_t current_state;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS W FILE LEVEL SCOPE//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

static void callback_B(void);
static void callback_A(void);
static void callback_timer(void);
static void encoder_state_machine(encoder_events_t ev);

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//					FUNCTION DEFINITIONS						//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void encoder_init(void){
/*****************************************************************
 * @brief: Initialize the encoder Driver
 * **************************************************************/
	static bool yaInit = false;
	if (yaInit)
		return;
	timerInit();
	encoder_timer = timerGetId();
	gpioMode(ENCODER_PIN_A, INPUT_PULLUP);
	gpioMode(ENCODER_PIN_B, INPUT_PULLUP);
	gpioIRQ (ENCODER_PIN_A, GPIO_IRQ_MODE_BOTH_EDGES, callback_A);
	gpioIRQ (ENCODER_PIN_B, GPIO_IRQ_MODE_BOTH_EDGES, callback_B);
	buttonInit();
	encoder_button = get_new_button(ENCODER_PIN_SW, INPUT_PULLUP);
	current_state = ENCODER_IDLE_ST;
	yaInit = true;
	return;
}

void encoder_set_callback(enc_callback_t  ccw, enc_callback_t  cw, enc_callback_t  click, enc_callback_t double_click, enc_callback_t long_click){
/*****************************************************************
 * @brief: Set the callbacks corresponding to the different types
 *			of modes
 * @param ccw: Callback for Counter-Clockwise turn.
 * @param cw: Callback for Clockwise turn.
 * @param click: Callback for button pressed single time.
 * @param double_click: Callback for button pressed double time.
 * @param long_click: Callback for button long press.
 * **************************************************************/
	callback_ccw=ccw;
	callback_cw=cw;
	callback_click=click;
	callback_double=double_click;
	callback_long=long_click;
	configure_button(encoder_button, callback_click,callback_long,callback_double);
	return;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//					LOCAL FUNCTION DEFINITIONS					//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

static void callback_B(void){
/*****************************************************************
 * @brief: Callback called by both edges of B encoder pin. It calls
 * 			the state machine handler with the corresponding event.
 * **************************************************************/
	if(gpioRead(ENCODER_PIN_B))
		encoder_state_machine(ENCODER_B_POSITIVE_EDGE_EV);
	else
		encoder_state_machine(ENCODER_B_NEGATIVE_EDGE_EV);
	return;
}

static void callback_A(void){
/*****************************************************************
 * @brief: Callback called by both edges of A encoder pin. It calls
 * 			the state machine handler with the corresponding event.
 * **************************************************************/
	if(gpioRead(ENCODER_PIN_A))
		encoder_state_machine(ENCODER_A_POSITIVE_EDGE_EV);
	else
		encoder_state_machine(ENCODER_A_NEGATIVE_EDGE_EV);
	return;
}

static void callback_timer(void){
/*****************************************************************
 * @brief: Callback called when the singleshot timer of the state
 * 			machine finishes. It calls the stame machine with the 
 * 			timer finished event.
 * **************************************************************/
	encoder_state_machine(ENCODER_TIMER_FINISHED_EV);
	return;
}

static void encoder_state_machine(encoder_events_t ev){
/*****************************************************************
 * @brief: Encoder state machines, it determines which state to go
 * 			whenever an event arrives. When the correct moment arrives
 * 			it calls the clockwise or conter-clockwise callbacks.
 * **************************************************************/
	switch(current_state){
		case ENCODER_IDLE_ST:
			if(ev == ENCODER_A_NEGATIVE_EDGE_EV){
				current_state = ENCODER_CASE_1_0_ST;
			}
			else if(ev == ENCODER_B_NEGATIVE_EDGE_EV){
				current_state = ENCODER_CASE_2_0_ST;
			}
			break;
		case ENCODER_CASE_1_0_ST:
			if(ev == ENCODER_B_NEGATIVE_EDGE_EV){
				current_state = ENCODER_CASE_1_1_ST;
			}
			break;
		case ENCODER_CASE_1_1_ST:
			if(ev == ENCODER_A_POSITIVE_EDGE_EV){
				current_state = ENCODER_CASE_1_2_ST;
			}
			break;
		case ENCODER_CASE_1_2_ST:
			if(ev == ENCODER_B_POSITIVE_EDGE_EV){
				gpioDisableIRQ(ENCODER_PIN_B);
				timerStart(encoder_timer,ENCODER_TIME_TIMER,TIM_MODE_SINGLESHOT,callback_timer);
				current_state = ENCODER_CASE_1_3_ST;
			}
			break;
		case ENCODER_CASE_1_3_ST:
			if(ev == ENCODER_TIMER_FINISHED_EV){
				callback_ccw();
				current_state = ENCODER_IDLE_ST;
				gpioIRQ (ENCODER_PIN_B, GPIO_IRQ_MODE_BOTH_EDGES, callback_B);
			}
			break;
		case ENCODER_CASE_2_0_ST:
			if(ev == ENCODER_A_NEGATIVE_EDGE_EV){
				current_state = ENCODER_CASE_2_1_ST;
			}
			break;
		case ENCODER_CASE_2_1_ST:
			if(ev == ENCODER_B_POSITIVE_EDGE_EV){
				current_state = ENCODER_CASE_2_2_ST;
			}
			break;
		case ENCODER_CASE_2_2_ST:
			if(ev == ENCODER_A_POSITIVE_EDGE_EV){
				gpioDisableIRQ(ENCODER_PIN_A);
				timerStart(encoder_timer,ENCODER_TIME_TIMER,TIM_MODE_SINGLESHOT,callback_timer);
				current_state = ENCODER_CASE_2_3_ST;
			}
			break;
		case ENCODER_CASE_2_3_ST:
			if(ev == ENCODER_TIMER_FINISHED_EV){
				callback_cw();
				current_state = ENCODER_IDLE_ST;
				gpioIRQ (ENCODER_PIN_A, GPIO_IRQ_MODE_BOTH_EDGES, callback_A);
			}
			break;
		default:
			current_state = ENCODER_ERROR_ST;
			break;
	}
	return;
}
