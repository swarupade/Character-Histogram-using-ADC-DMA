
//*****************************************************************************
// Name        : resize_CB
//
// Description : Function to resize the existing circular Buffer
//
// Author      : Steve and Swarupa
//
// Date        : Nov 06, 2018
//
// Arguments   : elements_to_add - No. of elements to the added to the circular buffer inorder to resize it
//
// return      : status
//				 SUCCESS on completion, otherwise ERROR
//
//****************************************************************************/


//***********************************************************************************
// Include files
//***********************************************************************************
#include "resize_CB.h"

//***********************************************************************************
// Function definition
//***********************************************************************************
status resize_CB(CB *buffer, int32_t elements_to_add)
{
	//checks if it is a null pointer
	if(buffer==NULL)
	{
		PRINT("Null pointer input\r\n");
		return NULL_PTR;
	}

	//check if the number of elements to be added is valid number
	if(elements_to_add<=0)
	{
		PRINT("elements_to_add input is not valid\r\n");
		return ERROR;
	}

	//check if the buffer is initialised
	else if((buffer->flag_init) != 1)
	{
		PRINT("Buffer not initialized\r\n");
		return BUFFER_NOT_INITIALISED;
	}

	//resizing
	else
	{
		for(int i=1; i<=elements_to_add;i++)
		{
			if((insert_link(buffer)) == ERROR)
			{
				PRINT("No space in memoryr\n");
				return ERROR;
			}
        }
    }
	return SUCCESS;
}
