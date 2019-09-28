/**
* @file common_variable.h
* @brief contains the variables used across other files
*
*
* @author Steve and Swarupa
* @date Nov 7, 2018
*
*/
//***********************************************************************************
// Include files
//***********************************************************************************
#ifndef _COMMON_VARIABLE_H_
#define  _COMMON_VARIABLE_H_
#include <stdint.h>

//***********************************************************************************
// Macros
//***********************************************************************************

//------------------------------------------------------------------------
// Mode selection in FRDM : POLLING OR INTERRUPT

//define FRDM
//#define INTERRUPT
#define POLLING

//#define DEBUG
//------------------------------------------------------------------------


// Print function

#ifdef FRDM
	#define PRINT send_to_console_str
#endif

#ifdef LINUX
	#define PRINT printf
#endif

//***********************************************************************************
// Globals
//***********************************************************************************

//Error handling enums
typedef enum status_t
{
	NULL_PTR = -5,
	OVERFLOW = -4,
	EMPTY = -3,
	BUFFER_NOT_INITIALISED = -2,
	ERROR = -1,
	SUCCESS = 1,
}status;


// Node for Circular Linked List
struct node
{
	uint8_t data;
	struct node * link;
};


//Circular buffer declaration
typedef struct
{
	struct node* front_CB;
	struct node* rear_CB;
	struct node *head;
	struct node *tail;
	int32_t length_CB;
	int32_t max_size;
	int8_t flag_init;
}CB;



CB RX_buffer ;

#endif
