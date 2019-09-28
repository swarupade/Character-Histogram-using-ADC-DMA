//*****************************************************************************
// Name        : clear_buffer
//
// Description : Function to clear the data present in circular buffer
//
// Author      : Steve and Swarupa
//
// Date        : Nov 07, 2018
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
#include "clear_buffer.h"

//***********************************************************************************
// Function definition
//***********************************************************************************

status clear_buffer(CB *buffer)
{
	//checks if it is a null pointer
	if(buffer==NULL)
    {
        PRINT("Null pointer input\r\n");
        return NULL_PTR;
    }
	
	//Check if the buffer is not initialized
	if((buffer->flag_init) != 1)
	{
		PRINT("Buffer not initialized\r\n");
		return BUFFER_NOT_INITIALISED;
	}

	//check if the buffer is empty
	else if(IsEMPTY(buffer))
	{
		PRINT("Nothing to clear: Buffer is empty\r\n");
		return EMPTY;
	}
	
	//clearing the buffer contents
	else
	{
		(buffer->front_CB) = (buffer->head);
		(buffer->rear_CB) = (buffer->head);
		(buffer->length_CB) = 0;
		PRINT("Cleared the buffer\r\n");
		return SUCCESS;
	}
}
