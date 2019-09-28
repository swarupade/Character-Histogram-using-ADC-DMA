/**
* @file uart.c
*
* This file contains function configuring, tranmitting and receiving part of UART0
*
* @author Steve and Swarupa
* @date Nov 24, 2018
*
*/

//***********************************************************************************
// Include files
//***********************************************************************************
#include "MKL25Z4.h"
#include "uart.h"
#include "main.h"
#include <stdlib.h>
#include <string.h>

//declare rx_buffer and tx_buffer for data manipulation
extern uint8_t data_pop;
extern uint32_t database[256] ;
//variable to store the received data
extern uint8_t data_poll;

//Flag to indicate that a data is received
extern int8_t FLAG_RECV;

//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : uartinit
//
// Description : Function to initiate UART0
//
// Arguments   : None
//
// return      : None
//
//****************************************************************************/
void uartinit()
{

		    uint16_t baudmoddivisor;

		   //Set gate clock  for PORTA
			SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

			//Enable clock for UART0
			SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

			// Set the alternate function for PORTA as UART0
			PORTA_PCR1 |= PORT_PCR_MUX(0x2);
			PORTA_PCR2 |= PORT_PCR_MUX(0x2);

			//set clock source as MCGPLLCLK/2
			SIM_SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK);

			SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
			//SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(1);

			// Disable tx and rx before editing registers of UART0
			UART0_C2 |= (UART0_C2_TE(0) | UART0_C2_RE(0));


			//calculate the baud rate modulo divisor and set the baud rate
			UART0_BDH &= ~UART0_BDH_SBR_MASK;
			UART0_BDL &= ~UART0_BDL_SBR_MASK;

			baudmoddivisor= (uint16_t)((SystemCoreClock)/(UART0_BAUD_RATE *16));
			UART0_BDH |= UARTLP_BDH_SBR((baudmoddivisor >> 8)) ;
			UART0_BDL |= UARTLP_BDL_SBR(baudmoddivisor);

			//Selecting 8 bit data, No parity
			UART0_C1 |= UART0_C1_M(0) | UART_C1_PE(0);

			//selecting one stop bit
			UART0_BDH |= UART_BDH_SBNS(0);


			//Enabling the Transmitter enable and receiver enable bit
			UART0_C2 |= (UART0_C2_TE(1) | UART0_C2_RE(1));



}

//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : RX_interrupt_init
//
// Description : Function to activate receive interrupt in UART0
//
// Arguments   : None
//
// return      : None
//
//****************************************************************************/

void RX_interrupt_init()
{

	NVIC_EnableIRQ(UART0_IRQn);

	//enabling RIE
	UART0_C2 |= (UART_C2_RIE_MASK);

}

//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : send_to_console_str
//
// Description : Function to transmit a string
//
// Arguments   : string to be transmitted
//
// return      : None
//
//****************************************************************************/
void send_to_console_str(char data[])
{
	for(int i =0; data[i] != '\0'; i++)
	{
		//polling for transmitting
		while(!(UART0_S1 & UART_S1_TDRE_MASK));
		UART0_D = (data[i]);
		while(!(UART0_S1 & UART_S1_TC_MASK));
	}
}

//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : send_to_console
//
// Description : Function to transmit a byte
//
// Arguments   : byte to be transmitted
//
// return      : None
//
//****************************************************************************/
void send_to_console(uint8_t data)
{
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	UART0_D = (data);
	while(!(UART0_S1 & UART_S1_TC_MASK));
}



//***********************************************************************************
// RX ISR definition
//***********************************************************************************

//*****************************************************************************
// Name        : UART0_IRQHandler
//
// Description : IRQ for receive interrupt
//
// Arguments   : None
//
// return      : None
//
//****************************************************************************/
void UART0_IRQHandler()
{
	if((UART0_S1) & (UART0_S1_RDRF_MASK))
		{
			PTB->PCOR = (1<<18); //on red

			//insert byte to circular buffer
			insert_data(&RX_buffer, UART0_D);

			//pop data from circular buffer
			pop_data(&RX_buffer,&data_pop);

			//updating the count database
			database[data_pop] = database[data_pop] + 1;

			//initiating the systick timer
			sys_reload();
			PTB->PSOR = (1<<18); // off red
		}
}

//*****************************************************************************
// Name        : receiver_polling
//
// Description : receiver function when polling mode is chosen
//
// Arguments   : None
//
// return      : None
//
//****************************************************************************/
void receiver_polling()
{
	data_poll = UART0_D;
	FLAG_RECV = 1;
}
//*****************************************************************************
// Name        : transmitter_polling
//
// Description : transmitter function when polling mode is chosen
//
// Arguments   : None
//
// return      : None
//
//****************************************************************************/
void transmitter_polling()
{
	UART0_D = data_poll;
}
