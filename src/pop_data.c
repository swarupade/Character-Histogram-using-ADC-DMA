
//*****************************************************************************
// Name        : pop_data
//
// Description : Function to pop data out of circular Buffer
//
// Author      : Steve and Swarupa
//
// Date        : Nov 18, 2018
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
#include "pop_data.h"

//***********************************************************************************
// Function definition
//***********************************************************************************

status pop_data(CB *buffer,uint8_t *data)
{

	//checks if it is a null pointer
	if(buffer==NULL)
	{
		PRINT("Null pointer input\r\n");
		return NULL_PTR;
	}

	*data = 0;

	//check if the buffer is initialised
	if((buffer->flag_init) != 1)
	{
		PRINT("Buffer not initialized\r\n");
		return BUFFER_NOT_INITIALISED;
	}

	//check if the buffer is empty
	else if(IsEMPTY(buffer))
	{
		PRINT("Nothing to pop: Buffer is empty\r\n");
		return EMPTY;

	}

	//pop data
	else
	{
		(*data) = ((buffer->front_CB) -> data);
		(buffer->front_CB) = ((buffer->front_CB) -> link);
		(buffer->length_CB)--;
		return SUCCESS;
	}
}
