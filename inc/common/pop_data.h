/**
* @file pop_data.h
* @brief An abstraction for pop_data.c
*
* This header file provides declarations of pop_data.c
*
* @author Steve and Swarupa
* @date Nov 18, 2018
*
*/
//***********************************************************************************
// Include files
//***********************************************************************************

#ifndef _POP_DATA_H_
#define _POP_DATA_H_


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
status pop_data(CB *,uint8_t *);
int8_t IsEMPTY(CB *);


#endif
