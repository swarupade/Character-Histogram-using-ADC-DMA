/**
* @file clear_buffer.h
* @brief An abstraction for clear_buffer.c
*
* This header file provides declarations of clear_buffer.c
*
* @author Steve and Swarupa
* @date Nov 7, 2018
*
*/
//***********************************************************************************
// Include files
//***********************************************************************************

#ifndef _CLEAR_BUFFER_H_
#define _CLEAR_BUFFER_H_


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "common_variable.h"

#ifdef FRDM
#include "uart.h"

#endif
//***********************************************************************************
// function prototypes
//***********************************************************************************
status clear_buffer(CB *);
int8_t IsEMPTY(CB *);

#endif
