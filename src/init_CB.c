/**
* @file init_CB.c
*
* This file contains function for checking if the circular buffer is empty, full 
* and initiating the circular buffer
*
* @author Steve and Swarupa
* @date Nov 6, 2018
*
*/

//***********************************************************************************
// Include files
//***********************************************************************************
#include "init_CB.h"

//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : init_CB
//
// Description : Function to initiate a circular buffer
//
// Arguments   : length - Length of the circular buffer to be created
//
// return      : SUCCESS if it is created successfully, otherwise ERROR
//
//****************************************************************************/


status init_CB(CB *buffer,int32_t length)
{
	//checks if it is a null pointer
	if(buffer==NULL)
    {
        PRINT("Null pointer input\r\n");
        return NULL_PTR;
    }

	//check if the length is valid
	if(length<=0)
	{
		PRINT("Not a valid length\r\n");
		return ERROR;
	}

	(buffer->head) = NULL;
	(buffer->tail) = NULL;
	(buffer->front_CB) = NULL;
	(buffer->rear_CB) = NULL;
	(buffer->length_CB) = 0;
	(buffer->max_size) = 0;
	(buffer->flag_init) = 0;

	

	//creating the circular buffer
	
			//flag for buffer initialisation
		(buffer->flag_init) = 1;

		//circular linked list creation
		for(int i=1; i<=length;i++)
		{
			if((insert_link(buffer)) == ERROR)
			{
				PRINT("No space to allocate\r\n");
				return ERROR;
			}
        }
    

    
    (buffer->front_CB) = (buffer->head);
    (buffer->rear_CB) = (buffer->head);

	return SUCCESS;
}

//*****************************************************************************
// Name        : IsFULL
//
// Description : Function to check if the circular buffer is FULL
//
// Arguments   : No
//
// return      : 1 if it is Full, otherwise 0
//
//****************************************************************************/

int8_t IsFULL(CB *buffer)
{
	if((buffer->length_CB) == (buffer->max_size))
		return 1;
	else
		return 0;
}


//*****************************************************************************
// Name        : IsEMPTY
//
// Description : Function to check if the circular buffer is Empty
//
// Arguments   : No
//
// return      : 1 if it is Empty, otherwise 0
//
//****************************************************************************/
int8_t IsEMPTY(CB *buffer)
{
	if((buffer->length_CB) == 0)
		return 1;
	else
		return 0;
}

