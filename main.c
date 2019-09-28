/**
* @file main.c
*
*
* @author Steve and Swarupa
* @date Nov 6, 2018
*
*/

//***********************************************************************************
// Include files
//***********************************************************************************


#include "main.h"


//***********************************************************************************
// Globals
//***********************************************************************************

uint32_t database[256] = {0};
uint8_t data_pop = 0;
char num[20];
uint32_t prime_number;
char prime_print[30];
//variable to store the received data
uint8_t data_poll = 0;

//Flag to indicate that a data is received
int8_t FLAG_RECV = 0;

//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : main
//
// Description : main function
//
// Arguments   : none
//
// return      : unused
//
//****************************************************************************/


int main(void)
{


#ifdef LINUX
	init_CB(&RX_buffer,5);

	delete_CB(&RX_buffer);
	delete_CB(&RX_buffer);

	report_data(&RX_buffer);


#endif

#ifdef FRDM


	//Interrupt mode - Character Histogram application
#ifdef INTERRUPT

	//initiating UART0
	uartinit();

	//Initiating UART Rx interrupt
	RX_interrupt_init();

	//Initiating LED Red
	LED_init_IRQ();

	send_to_console_str("Welcome to Character Histogram Application\r\n");

	//initiating the circular buffer
	init_CB(&RX_buffer, SIZE_OF_RX_CB);

	PTB->PSOR |= (1<<18);//off LED red

	while(1)
	{

	    uint32_t value,divisor,Exact_divisible_count;

	    //Prime number generator
	    for(value=2;value<MAX_PRIME_NUMBER;value++)
		{
	    	Exact_divisible_count =0;

			for(divisor=1;divisor<=value;divisor++)
			{
				//Checks if the remainder is zero
				if(value%divisor == 0)
				{
					Exact_divisible_count++;
				}
			}

			//If Exact_divisible_count=2, it is a prime number
			if(Exact_divisible_count==2)
			{
			    prime_number = value ;
			}

		}
	}

#else

	//polling mode - echoing characters


	//configuring interrupt
	uartinit();



	while(1)
	{
		// Receiver polling
		while(UART0_S1 & UART0_S1_RDRF_MASK)
		{
			receiver_polling();
		}

		//Transmitting
		while(FLAG_RECV == 1)
		{
			while(UART0_S1 & UART0_S1_TDRE_MASK)
			{
				transmitter_polling();
			}
			FLAG_RECV = 0;
		}

	}
#endif
#endif

	return 1;
}

#ifdef FRDM
//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : sys_reload
//
// Description : function to reload the systick timer
//
// Arguments   : none
//
// return      : unused
//
//****************************************************************************/
void sys_reload()
{
	SYSTICK_VAL = 0x0;    //clear current timer value
	SYSTICK_LOAD = 0xFFFFFFF; //loading value
	SYSTICK_CTRL = 0x7; //enabling systick interrupt
}

//***********************************************************************************
// Systick ISR definition
//***********************************************************************************

//*****************************************************************************
// Name        : SysTick_Handler
//
// Description : ISR for systick timer which has the report generation part
//
// Arguments   : none
//
// return      : unused
//
//****************************************************************************/
void SysTick_Handler(void)
{
	PTB->PCOR = (1<<18); //on red LED

	PRINT("\r\n\r\n");
	PRINT("Report:\r\n");

	//Report Generation Part
	for(int i =0;i<MAX_ASCII;i++)
	{
		if(database[i]!= 0)
		{
			sprintf(num," %c - %lu \r\n",i,database[i]);
			PRINT(num);
		}
	}


	//Triangle pattern generation using prime number

	sprintf(prime_print,"%lu ",prime_number);

	PRINT("---------------------------------\r\n");
	//Pattern
	for(int row=1; row<=ROWS_PATTERN_MAX; row++)
	{
	     for(int column=1; column<=row; column++)
	      {
	    		PRINT(prime_print);
	      }
	     PRINT("\r\n");
	}

	// disabling the systick interrupt
	SYSTICK_CTRL = 0x0;

	PTB->PSOR = (1<<18); // off red LED
}
//*****************************************************************************
// Name        : LED_init_IRQ
//
// Description : For initiating LED
//
// Arguments   : none
//
// return      : unused
//
//****************************************************************************/
void LED_init_IRQ()
{
	//Clock for PORT B
	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTB_MASK;

	//Alternate function selection for PIN 18 of PORT B
	PORTB_PCR18 |= PORT_PCR_MUX(0x1);

	PTB->PDDR |= (1<<18); // selecting as output pin

}
#endif
