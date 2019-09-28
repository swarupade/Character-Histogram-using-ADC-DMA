/************************************************************************************
 * Filename: Unittest1.c
 * Author : Steve and Swarupa
 *
 * Description : This file tests each and every functionality used individually using CUnits
 *
 * *********************************************************************************/

 /**********************************************************/
 //    Includes
 /**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../inc/common/common_variable.h"
#include "CUnit/Basic.h"
#include "../inc/common/main.h"
#include <time.h>

 /**********************************************************/
 //    MACROS
 /**********************************************************/

#define MAX_DATA_VALUE (255) // largest value of ascii
#define MAX_ARRAY_LENGTH (1000)
#define MIN_ARRAY_LENGTH (10)

 /**********************************************************/
 //    GLOBALS
 /**********************************************************/
uint8_t *p = NULL;
uint8_t data_pop= 0;
uint8_t parameter_value[2000] = {0};
CB buffer_1;
CB buffer_2;
CB buffer_3;
CB buffer_4;
CB buffer_5;
CB buffer_6;
CB buffer_7;
CB buffer_8;

int32_t CB_SIZE = 0;


//***********************************************************************************
// Function definition
//***********************************************************************************

//*****************************************************************************
// Name        : random_generator
//
// Description : Generate an array of random number for giving as input in various functions
//
// Arguments   : none
//
// return      : unused
//
//****************************************************************************/

/*random value generator function */
int random_generator()
{

  for(uint32_t i= 0; i< CB_SIZE; i++) 
    {
     //limiting the random value to be within max value of ASCII
     parameter_value[i] = (rand() % MAX_DATA_VALUE );
    }
    return 0;

}  

//***********************************************************************************
// initiating suite
//***********************************************************************************

/*Suite 1*/
int init_suite_init_CB(void)
{
	return 0;
}

/*Suite 2*/
int init(void)
{
	init_CB(&buffer_2, (CB_SIZE));
	init_CB(&buffer_3, (CB_SIZE));
	return 0;

}

/*Suite 3*/
int init_delete(void)
{
	init_CB(&buffer_4, (CB_SIZE));
	return 0;
}

/*Suite 4*/
int init_suite_report_data(void)
{
    init_CB(&buffer_5, (CB_SIZE));
	return 0;
}

/*Suite 5*/

int init_suite_resize(void)
{
    init_CB(&buffer_6, (CB_SIZE));
    init_CB(&buffer_7, (CB_SIZE));
        
	return 0;
}

/*Suite 6*/
int init_suite_clear(void)
{
    init_CB(&buffer_8, (CB_SIZE));
     uint32_t i;
        
	for(p= parameter_value,i=0; i<CB_SIZE ; i++, p++)
	{
		insert_data(&buffer_8,*p);
	}
	return 0;
}

//***********************************************************************************
// Cleaning suite
//***********************************************************************************

int clean_suite(void)
{
	return 0;
}

//***********************************************************************************
// Adding test registry
//***********************************************************************************

void test_init_CB() //suite1
{
	
     p= parameter_value;  
     
     CB *circular_buffer;
     circular_buffer = NULL; 

     //NULL pointer check
    CU_ASSERT_EQUAL(init_CB(circular_buffer, 5), NULL_PTR);
    CU_ASSERT_EQUAL(insert_data(circular_buffer,*p),NULL_PTR);
	CU_ASSERT_EQUAL(delete_CB(circular_buffer),NULL_PTR);
	CU_ASSERT_EQUAL(report_data(circular_buffer),NULL_PTR);
	CU_ASSERT_EQUAL(clear_buffer(circular_buffer),NULL_PTR);
	CU_ASSERT_EQUAL(resize_CB(circular_buffer,*p),NULL_PTR);
	CU_ASSERT_EQUAL(pop_data(circular_buffer,&data_pop),NULL_PTR);	

	//Check when the Circular buffer functions are called without initializing the circular buffer
	CU_ASSERT_EQUAL(insert_data(&buffer_1,*p),BUFFER_NOT_INITIALISED);
	CU_ASSERT_EQUAL(delete_CB(&buffer_1),BUFFER_NOT_INITIALISED);
	CU_ASSERT_EQUAL(report_data(&buffer_1),BUFFER_NOT_INITIALISED);
	CU_ASSERT_EQUAL(clear_buffer(&buffer_1),BUFFER_NOT_INITIALISED);
	CU_ASSERT_EQUAL(resize_CB(&buffer_1,*p),BUFFER_NOT_INITIALISED);
	CU_ASSERT_EQUAL(pop_data(&buffer_1,&data_pop),BUFFER_NOT_INITIALISED);


	CU_ASSERT_EQUAL(init_CB(&buffer_1, -1), ERROR);
	CU_ASSERT_EQUAL(init_CB(&buffer_1, 0), ERROR);
	CU_ASSERT_EQUAL(init_CB(&buffer_1, 1), SUCCESS);

	CU_ASSERT_EQUAL(init_CB(&buffer_1,*p),SUCCESS);


	CU_ASSERT_EQUAL(delete_CB(&buffer_1), SUCCESS);

}

void test_insert_data() //suite2
{
	uint32_t i;

	//inserting elements
    for(p= parameter_value,i=0; i<(CB_SIZE) ; i++, p++)
	{
		CU_ASSERT_EQUAL(insert_data(&buffer_2,*p),SUCCESS);

	}
	
	//Buffer overflow
	for(p= parameter_value,i=0; i<(CB_SIZE) ; i++, p++)
	{			
			CU_ASSERT_EQUAL(insert_data(&buffer_2,*p),-4);
		
	}
	
	//boundary conditions
	CU_ASSERT_EQUAL(insert_data(&buffer_3, '0'),SUCCESS);
	CU_ASSERT_EQUAL(insert_data(&buffer_3, '&'),SUCCESS);
	CU_ASSERT_EQUAL(insert_data(&buffer_3, ','),SUCCESS);
	CU_ASSERT_EQUAL(insert_data(&buffer_3, '\n'),SUCCESS);
	CU_ASSERT_EQUAL(insert_data(&buffer_3, ' '),SUCCESS);
	CU_ASSERT_EQUAL(insert_data(&buffer_3, 'z'),SUCCESS);
	CU_ASSERT_EQUAL(insert_data(&buffer_3, '\\'),SUCCESS); 
	CU_ASSERT_EQUAL(insert_data(&buffer_3, 5),SUCCESS); 
	CU_ASSERT_EQUAL(insert_data(&buffer_3, 0),SUCCESS);      
    


	CU_ASSERT_EQUAL(delete_CB(&buffer_2), SUCCESS);
	CU_ASSERT_EQUAL(delete_CB(&buffer_3), SUCCESS);

  
   
}

void test_delete_data() //suite3
{

	uint32_t i;
	for(i=0; i<CB_SIZE ; i++)
	{
		if(i == 0)
		{
			CU_ASSERT_EQUAL(delete_CB(&buffer_4),SUCCESS);
		}
		else
		{
			CU_ASSERT_EQUAL(delete_CB(&buffer_4),BUFFER_NOT_INITIALISED);
		}
	}

}

void test_pop_and_report_data() //suite4
{
	uint32_t i;

	//inserting elements - success
  	for(p= parameter_value,i=0; i<(CB_SIZE) ; i++, p++)
	{
		CU_ASSERT_EQUAL(insert_data(&buffer_5,*p),SUCCESS);
	}

	//report data - success
	for(i=0; i<(CB_SIZE) ; i++)
	{
		
		CU_ASSERT_EQUAL(report_data(&buffer_5),SUCCESS);
	}

	//pop data - success
	for(i=0; i<(CB_SIZE) ; i++)
	{
		
			CU_ASSERT_EQUAL(pop_data(&buffer_5, &data_pop),SUCCESS);
	}

	//report data - empty
	for(i=0; i<(CB_SIZE) ; i++)
	{
		
		CU_ASSERT_EQUAL(report_data(&buffer_5),EMPTY);
	}

	//pop data - empty
	for(i=0; i<(CB_SIZE) ; i++)
	{
		
			CU_ASSERT_EQUAL(pop_data(&buffer_5, &data_pop),EMPTY);
	}
	

	CU_ASSERT_EQUAL(delete_CB(&buffer_5),SUCCESS);
}

void test_resize_CB() //suite5
{
	uint32_t i;

	//insert data - success
     for(p= parameter_value,i=0; i<(CB_SIZE) ; i++, p++)
	{
		CU_ASSERT_EQUAL(insert_data(&buffer_6,*p),SUCCESS);
	}

	//insert data - overflow
	CU_ASSERT_EQUAL(insert_data(&buffer_6,parameter_value[0]),-4);

	//resize
	CU_ASSERT_EQUAL(resize_CB(&buffer_6,CB_SIZE),SUCCESS);

	//insert data - success
	 for(p= parameter_value,i=0; i<(CB_SIZE) ; i++, p++)
	{
		CU_ASSERT_EQUAL(insert_data(&buffer_6,*p),SUCCESS);
	}

	//boundary cases
	CU_ASSERT_EQUAL(resize_CB(&buffer_7,-2),ERROR);
	CU_ASSERT_EQUAL(resize_CB(&buffer_7,0),ERROR);


	CU_ASSERT_EQUAL(delete_CB(&buffer_6),SUCCESS);
	CU_ASSERT_EQUAL(delete_CB(&buffer_7),SUCCESS);



}

void test_clear_buffer() //suite5
{

   CU_ASSERT_EQUAL(clear_buffer(&buffer_8),SUCCESS);
   CU_ASSERT_EQUAL(clear_buffer(&buffer_8),EMPTY);

}

//*****************************************************************************
// Name        : main function
//
// Description : contains the call of the suites for unit testing
//
// Arguments   : none
//
// return      : unused
//
//****************************************************************************/
int main(void)
{

	 if (CUE_SUCCESS != CU_initialize_registry())
	return CU_get_error();

	CU_pSuite pSuite1 = NULL;
    /* initialize the CUnit test registry */
   

 	/* add a suite to the registry */
 	pSuite1 = CU_add_suite("Suite_1", init_suite_init_CB, clean_suite);
    if (NULL == pSuite1)
    {
	 	CU_cleanup_registry();
	    return CU_get_error();
	}

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite1, "test of fprintf()", test_init_CB)))
    {
	    CU_cleanup_registry();
      	return CU_get_error();
	}
/***************************************************************************/

	CU_pSuite pSuite2 = NULL;
    
 	/* add a suite to the registry */
 	pSuite2 = CU_add_suite("Suite_2", init, clean_suite);
    if (NULL == pSuite2)
    {
	 	CU_cleanup_registry();
	    return CU_get_error();
	}


	if ((NULL == CU_add_test(pSuite2, "test of fprintf()", test_insert_data)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

/***************************************************************************/

	CU_pSuite pSuite3 = NULL;
    

 	/* add a suite to the registry */
 	pSuite3 = CU_add_suite("Suite_3", init_delete, clean_suite);
    if (NULL == pSuite3)
    {
		CU_cleanup_registry();
	    return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite3, "test of fprintf()", test_delete_data)))
	{
	    CU_cleanup_registry();
	    return CU_get_error();
	}
/***************************************************************************/

	CU_pSuite pSuite4 = NULL;
    

 	/* add a suite to the registry */
 	pSuite4 = CU_add_suite("Suite_4", init_suite_report_data, clean_suite);
    if (NULL == pSuite4)
    {
		CU_cleanup_registry();
	    return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite4, "test of fprintf()", test_pop_and_report_data)))
	{
	        CU_cleanup_registry();
	        return CU_get_error();
	}
/***************************************************************************/

	CU_pSuite pSuite5 = NULL;
    

 	/* add a suite to the registry */
 	pSuite5 = CU_add_suite("Suite_5", init_suite_resize, clean_suite);
    if (NULL == pSuite5)
    {
		CU_cleanup_registry();
	    return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite5, "test of fprintf()", test_resize_CB)))
	{
	        CU_cleanup_registry();
	        return CU_get_error();
	}

/***************************************************************************/

	CU_pSuite pSuite6 = NULL;
    

 	/* add a suite to the registry */
 	pSuite6 = CU_add_suite("Suite_6", init_suite_clear, clean_suite);
    if (NULL == pSuite6)
    {
		CU_cleanup_registry();
	    return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite6, "test of fprintf()", test_clear_buffer)))
	{
	        CU_cleanup_registry();
	        return CU_get_error();
	}

/***************************************************************************/
    /* Run all tests using the CUnit Basic interface */
    time_t t;
    /* Intializes random number generator */
   srand((unsigned) time(&t));

  //parameter generation for circular buffer length

  refetch:
    CB_SIZE = ((rand()) % MAX_ARRAY_LENGTH);

    if((CB_SIZE < MIN_ARRAY_LENGTH))
    {
    	goto refetch;
    }

    printf("CB Length  %d\n",CB_SIZE);
    random_generator();
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
return CU_get_error();
}
