/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab13.c   
|  DATE:          FEB 2019
|  DESCRIPTION:   Arrays
********************************************************************************/

/*-------------------------------------------------------------------------------
  HEADER FILES
-------------------------------------------------------------------------------*/
#include <stdio.h>              // Standard I/O - required for printf() function
#include "PrintArray.h"         // Print out array elements

/*-------------------------------------------------------------------------------
  PROGRAM CONSTANTS
-------------------------------------------------------------------------------*/
#define ARRAY_SIZE 10

/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/
/*###############################################################################
# STEP 1: Create two initialized arrays with 10 elements each named array1 and 
#         array2 (you may use the pre-defined constant ARRAY_SIZE as part of the
#         array declaration).
#         The arrays should be initialized with the following values:
#         + array1: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
#         + array2: 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#         Note: the elements are all of type int
###############################################################################*/

//### Your Code Here ###        //### array1 declaration & definition

//### Your Code Here ###        //### array2 declaration & definition

	
int result[ARRAY_SIZE];

int multiDimArray[2][3] = {{ 6 , 3 , 12 } , { 4 , 8 , 68 }};

int i;

/*-------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
-------------------------------------------------------------------------------*/
int main(void);
int add_function( int m, int n );

/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  
  PARAMETERS:   none
  RETURNS:      0
  REQUIREMENTS: add_function(), PrintArray.c
===============================================================================*/
int main ( void )
{
	i = 0;
	
    while (i < ARRAY_SIZE)
    {
/*###############################################################################
# STEP 2: Pass the two arrays you declared above (array1 & array2) to the
#         function add_function() (see its definition below).  Store the result
#         of the function call in the array result[].  The idea here is to add
#         each corresponding element of array1 and array2 and store the result
#         in result[].  In other words, add the first element of array1[] to the
#         first element of array2[] and store the result in the first element of
#         result[].  Next add the second elements, and so on.
###############################################################################*/

        //### Your Code Here ###        //### result = sum of elements of array1 & array2


	   	i++;
	} 
	printArray(result, ARRAY_SIZE); 
	print2dArray(multiDimArray, 2);  //Function already knows size of second dimeinsion

    return 0;

}

/*===============================================================================
  FUNCTION:     add_function()
  DESCRIPTION:  Receives two variables, adds them and returns the sum.
  PARAMETERS:   int m, int n
  RETURNS:      Sum of m and n
  REQUIREMENTS: none
===============================================================================*/
int add_function( int m, int n)
{
    return (m + n);
}
