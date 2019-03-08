/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab14.c   
|  DATE:          FEB 2019
|  DESCRIPTION:   This lab will illustrate the syntax associated with 
|                 pointer assignment and usage.
********************************************************************************/

/*-------------------------------------------------------------------------------
  HEADER FILES
-------------------------------------------------------------------------------*/
#include <stdio.h>              // Standard I/O - required for printf() function

/*-------------------------------------------------------------------------------
  PROGRAM CONSTANTS
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/
int x = 5;
int y[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p;

/*-------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
-------------------------------------------------------------------------------*/
int main(void);

/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  Illustrates  
  PARAMETERS:   none
  RETURNS:      0
  REQUIREMENTS: none
===============================================================================*/
int main(void)
{	
	int i;

/*###############################################################################
# STEP 1: Initialize the pointer p with the address of the variable x
###############################################################################*/

	p = &x;        //### Point to address of x

/*###############################################################################
# STEP 2: Complete the following printf() functions by adding in the appropriate
#         arguments as described in the control string.
# NOTE:   This program will not build unless the following 5 lines of code are
#         completed and the comments are removed from the printf() functions.
###############################################################################*/	

	printf("The variable x is located at address %p\n", &x);
	printf("The value of x is %d\n", x);
	printf("The pointer p is located at address %p\n", &p);
	printf("The value of p is %p\n", p);
	printf("The value pointed to by *p = %d\n", *p);

/*###############################################################################
# STEP 3: Write the integer value 10 to the location p is currently pointing to.
###############################################################################*/

	*p = 10;	    //### x = 10 via pointer p (dereference)	
	
	printf("The variable x is located at address %p\n", &x);
	printf("The value of x is %d\n", x);
	
	//p = &y[0];                                  //p points to array y
    p = y;                                  //p points to array y
    printf("*&p  test %p \n", *&p);
    printf("&*p test %p \n", &*p);
/*-------------------------------------------------------------------------------
  Increment the value of each array element and print it out
-------------------------------------------------------------------------------*/	
	for (i = 0; i < sizeof(y)/sizeof(int); i++)
	{
/*###############################################################################
# STEP 4: Increment the value that p points to.
###############################################################################*/

	  (*p)++;       //### Increment array element's value
	  *p *= 10;
	  printf("y[%d] = %d\n", i, *p);
/*###############################################################################
# STEP 5: Increment the pointer p so that it points to the next item.
###############################################################################*/

	   p++;   //### Increment pointer to next array element					
	}


    return 0;	
}
