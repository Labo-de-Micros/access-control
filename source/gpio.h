//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//	@file		gpio.h										    //
//	@brief		Simple GPIO Pin services, similar to Arduino	//
//	@author		Grupo	4										//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#ifndef _GPIO_H_
#define _GPIO_H_

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

// Convert port and number into pin ID
// Ex: PTB5  -> PORTNUM2PIN(PB,5)  -> 0x25
//     PTC22 -> PORTNUM2PIN(PC,22) -> 0x56
#define PORTNUM2PIN(p,n)    (((p)<<5) + (n))
#define PIN2PORT(p)         (((p)>>5) & 0x07)
#define PIN2NUM(p)          ((p) & 0x1F)


// Modes
#ifndef INPUT
#define INPUT               0
#define OUTPUT              1
#define INPUT_PULLUP        2
#define INPUT_PULLDOWN      3
#endif // INPUT

// Digital values
#ifndef LOW
#define LOW     0
#define HIGH    1
#endif // LOW

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			ENUMERATIONS AND STRUCTURES AND TYPEDEFS			//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Ports
enum { PA, PB, PC, PD, PE };
// IRQ modes
enum {
	GPIO_IRQ_MODE_DISABLE,
	GPIO_IRQ_MODE_RISING_EDGE,
	GPIO_IRQ_MODE_FALLING_EDGE,
	GPIO_IRQ_MODE_BOTH_EDGES,
	GPIO_IRQ_CANT_MODES
};
typedef uint8_t pin_t;
typedef void (*pinIrqFun_t)(void);

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//			FUNCTION PROTOTYPES WITH GLOBAL SCOPE				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void gpioMode (pin_t pin, uint8_t mode);
/*****************************************************************
 * @brief Configures the specified pin to behave either as an input or an output
 * @param pin the pin whose mode you wish to set (according PORTNUM2PIN)
 * @param mode INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN.
 *****************************************************************/


void gpioWrite (pin_t pin, bool value);
/*****************************************************************
 * @brief Write a HIGH or a LOW value to a digital pin
 * @param pin the pin to write (according PORTNUM2PIN)
 * @param val Desired value (HIGH or LOW)
 *****************************************************************/


void gpioToggle (pin_t pin);
/*****************************************************************
 * @brief Toggle the value of a digital pin (HIGH<->LOW)
 * @param pin the pin to toggle (according PORTNUM2PIN)
 *****************************************************************/


bool gpioRead (pin_t pin);
/*****************************************************************
 * @brief Reads the value from a specified digital pin, either HIGH or LOW.
 * @param pin the pin to read (according PORTNUM2PIN)
 * @return HIGH or LOW
 *****************************************************************/


bool gpioIRQ (pin_t pin, uint8_t irqMode, pinIrqFun_t irqFun);
/*****************************************************************
 * @brief Configures how the pin reacts when an IRQ event ocurrs
 * @param pin the pin whose IRQ mode you wish to set (according PORTNUM2PIN)
 * @param irqMode disable, risingEdge, fallingEdge or bothEdges
 * @param irqFun function to call on pin event
 * @return Registration succeed
 *****************************************************************/

#endif // _GPIO_H_
