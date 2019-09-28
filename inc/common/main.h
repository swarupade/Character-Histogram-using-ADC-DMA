/**
* @file main.h
* @brief An abstraction for main.c
*
* This header file provides declarations of main.c
*
* @author Steve and Swarupa
* @date Nov 6, 2018
*
*/

//***********************************************************************************
// Include files
//***********************************************************************************

#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include "common_variable.h"

#ifdef FRDM
#include "uart.h"

#include "MKL25Z4.h"

//***********************************************************************************
// Macros for FRDM
//***********************************************************************************

#define MAX_PRIME_NUMBER (9999999)
#define MAX_ASCII (256)
#define ROWS_PATTERN_MAX (5)

//Macros for systick timer
#define SYSTICK_CTRL (*((volatile unsigned long *) (0xE000E010)))
#define SYSTICK_LOAD (*((volatile unsigned long *) (0xE000E014)))
#define SYSTICK_VAL (*((volatile unsigned long *) (0xE000E018)))

#endif

//***********************************************************************************
// Common Macros
//***********************************************************************************
#define SIZE_OF_RX_CB (30)


//***********************************************************************************
// Function prototypes
//***********************************************************************************

status resize_CB(CB *, int32_t );
status insert_link(CB *);
status insert_data(CB *,uint8_t);
int8_t IsEMPTY(CB *);
int8_t IsFULL(CB *);
status delete_CB(CB *);
status init_CB(CB *,int32_t);
status report_data(CB *);
status clear_buffer(CB *);
status pop_data(CB *,uint8_t *);
void LED_init_IRQ();
void receiver_polling();
void transmitter_polling();

#endif
