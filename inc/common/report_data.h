/**
* @file insert_link.h
* @brief An abstraction for insert_link.c
*
* This header file provides declarations of insert_link.c
*
* @author Steve and Swarupa
* @date Nov 6, 2018
*
*/

//***********************************************************************************
// Include files
//***********************************************************************************

#ifndef _REPORT_DATA_H_
#define _REPORT_DATA_H_

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
status report_data(CB *);
int8_t IsEMPTY(CB *);

#endif
