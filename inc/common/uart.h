/*
 * uart.h
 *
 *  Created on: Nov 7, 2018
 *      Author: Swarupa De
 */

//***********************************************************************************
// Include files
//***********************************************************************************

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#include "common_variable.h"

//***********************************************************************************
// Macros
//***********************************************************************************

#define UART0_BAUD_RATE (57600)


//***********************************************************************************
// Function Prototypes
//***********************************************************************************
void uartinit();
void RX_interrupt_init();
void send_to_console_str(char []);
void send_to_console(uint8_t);
void receiver_polling();
void transmitter_polling();

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
void sys_reload();


#endif /* INCLUDE_UART_H_ */

