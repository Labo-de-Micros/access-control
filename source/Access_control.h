#ifndef _ACCESSCONTROL_H
#define _ACCESSCONTROL_H



#include "StateMachine/DataTypes.h"
#include "StateMachine/State_machine.h"
#include <stdint.h>
#include <stdbool.h>



#define MAX_NUM_ATTEMPTS 3

#define MAX_DIGIT_DISPLAY 9
#define MIN_DIGIT_DISPLAY 0

#define MAX_BRIGHTNESS 10
#define MIN_BRIGHTNESS 1

#define MAX_IDS 2000

#define ERR_MSG_TIME 2

typedef enum{ 
	NEW_ID,
	ID,
	PIN4,
    PIN5
} word_option_t;



typedef struct{
    uint64_t card_id;
    uint32_t number; //Numero de ID (8 digitos)
    uint32_t PIN; //Contraseña del ID (4 o 5 digitos)
    uint8_t PIN_length;
    bool blocked_status; //Si el ID esta bloquedo es TRUE
    uint8_t PIN_attempts;
} ID_data_t;

// Access control object structure
typedef struct{
    uint16_t current_ID_index; // index ID actual 0,1,2,3 
    uint16_t total_of_IDs; //Cantidad de ids en la lista de IDS 

    uint8_t current_brightness; //Nivel de brillo actual

    //Manejo de introduccion de palabra
    uint8_t word_introduced[8]; //Palabra de 4,5 o 8 digitos
    uint8_t current_num; //Numero que se esta mostrando en el display
    uint8_t digits_introduced; //Cantidad de numeros introducidos 
    word_option_t current_option;


    ID_data_t IDsList[MAX_IDS]; 
} access_control_t;

/*
// Event data structure
typedef struct
{
    uint8_t id;
    word_option option;

} AccessControlData;
*/

// State machine event functions

EVENT_DECLARE(Encoder_Click, NoEventData);
EVENT_DECLARE(Encoder_Double_Click, NoEventData);
EVENT_DECLARE(Encoder_CW, NoEventData);
EVENT_DECLARE(Encoder_CCW, NoEventData);
EVENT_DECLARE(Encoder_Long_Click, NoEventData);
EVENT_DECLARE(Card_Reader, NoEventData);

#endif // _ACCESSCONTROL_H