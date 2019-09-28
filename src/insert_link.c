//*****************************************************************************
// Name        : insert_link.c
//
// Description : Function to insert a link to the circular linked list
//
// Author      : Steve and Swarupa
//
// Date        : Nov 06, 2018
//
// Arguments   : No
//
// return      : unused
//
//****************************************************************************/

//***********************************************************************************
// Include files
//***********************************************************************************
#include "insert_link.h"

//***********************************************************************************
// Function definition
//***********************************************************************************

status insert_link(CB *buffer)
{
    //checks if it is a null pointer
    if(buffer==NULL)
    {
        PRINT("Null pointer input\r\n");
        return NULL_PTR;
    }

    //creating a node
	struct node *temp = (struct node *) malloc (sizeof(struct node));
    if (temp == NULL)
    {
        PRINT("no memory space\r\n");
        return ERROR;
    }
    temp->data = '\0';
    temp->link = NULL;


    //for the first node
    if((buffer->head)!= NULL)
    {
    	(temp->link) = (buffer->head);
        (buffer->head) = temp;
        ((buffer->tail)->link) = (buffer->head);
    }

    //for nodes other than the first node
    else
    {
    	(buffer->head) = temp;
    	(buffer->tail) = temp;
		((buffer->tail) -> link) = temp;
    }
    (buffer->max_size)++;

    return SUCCESS;

}
