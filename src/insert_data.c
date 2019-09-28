
//*****************************************************************************
// Name        : insert_data
//
// Description : Function to insert data to the circular Buffer
//
// Author      : Steve and Swarupa
//
// Date        : Nov 06, 2018
//
// Arguments   : val - Data to be added
//
// return      : status
//				 SUCCESS on completion, otherwise ERROR
//
//****************************************************************************/


//***********************************************************************************
// Include files
//***********************************************************************************
#include "insert_data.h"

//***********************************************************************************
// Function definition
//***********************************************************************************

status insert_data(CB *buffer,uint8_t val)
{
	//checks if it is a null pointer
	if(buffer==NULL)
    {
        PRINT("Null pointer input\r\n");
        return NULL_PTR;
    }
	
	//check for buffer initialisation
	if((buffer->flag_init) != 1)
	{
		PRINT("Buffer not initialized\r\n");
		return BUFFER_NOT_INITIALISED;
	}

	//check for space in buffer
	else if(IsFULL(buffer))
	{
		PRINT("\nThe Buffer is FULL\r\n");
		PRINT("Adding failed\r\n");
		return OVERFLOW;
	}

	//adding elements in the buffer when it is added for the first time from empty state
	else if(((buffer->front_CB) == (buffer->rear_CB))&& (IsEMPTY(buffer)))
	{
		((buffer->rear_CB) -> data) = val;
		(buffer->length_CB)++;
#ifdef DEBUG
		PRINT("Added to the buffer\r\n");
		send_to_console((buffer->rear_CB) -> data);
		PRINT("\r\n");
#endif
		return SUCCESS;
	}

	//adding elements to the buffer
	else
	{
		(buffer->rear_CB) = ((buffer->rear_CB) -> link);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		((buffer->rear_CB) -> data) = val;
		(buffer->length_CB)++;
#ifdef DEBUG
		PRINT("Added to the buffer\r\n");
		send_to_console((buffer->rear_CB) -> data);
		PRINT("\r\n");
#endif
		return SUCCESS;
	}
}
