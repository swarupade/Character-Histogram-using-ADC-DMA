//*****************************************************************************
// Name        : report_data
//
// Description : Function to report the data present in circular buffer
//
// Author      : Steve and Swarupa
//
// Date        : Nov 06, 2018
//
// Arguments   : No
//
// return      : status
//				 SUCCESS on completion, otherwise ERROR
//
//****************************************************************************/


//***********************************************************************************
// Include files
//***********************************************************************************
#include "report_data.h"

//***********************************************************************************
// Function definition
//***********************************************************************************

status report_data(CB *buffer)
{
	//checks if it is a null pointer
	if(buffer==NULL)
	{
		PRINT("Null pointer input\r\n");
		return NULL_PTR;
	}
	
	//check if the buffer is initialised
	if((buffer->flag_init) != 1)
	{
		PRINT("Buffer not initialized\r\n");
		return BUFFER_NOT_INITIALISED;
	}

	//check if the buffer is empty
	else if(IsEMPTY(buffer))
	{
		PRINT("No data to display: Buffer is empty\r\n");
		return EMPTY;
	}


	// report data function
	else
	{
		struct node* temp;
		uint32_t count = 0;
		PRINT("\nElements in the circular buffer:\r\n");

		for((temp = (buffer->front_CB)); (temp!=(buffer->rear_CB));(temp= (temp->link)))
		{
			#ifdef FRDM
			send_to_console((temp->data));
			#else
			printf("%d", temp->data);
			#endif
			PRINT("\r\n");
			count ++;



		}

		//print last eleemnt of the buffer
		#ifdef FRDM
		send_to_console(((buffer->rear_CB)->data));
		#else
		printf("%d",((buffer->rear_CB)->data));
		#endif

		PRINT("\r\n");

		//print the count of elements
		#ifdef FRDM
		char count_str[30];
		sprintf(count_str,"Total elements present = %lu \r\n",(count+1));
		PRINT(count_str);
		#else
		printf("Total elements present = %u \n",(count+1));
		#endif

		return SUCCESS;
	}
}
