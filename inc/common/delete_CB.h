/**
* @file delete_data.h
* @brief An abstraction for delete_data.c
*
* This header file provides declarations of delete_data.c
*
* @author Steve and Swarupa
* @date Nov 6, 2018
*
*/
//***********************************************************************************
// Include files
//***********************************************************************************

#ifndef _DELETE_CB_H_
#define _DELETE_CB_H_


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
status delete_CB(CB *);
int8_t IsEMPTY(CB *);

#endif
