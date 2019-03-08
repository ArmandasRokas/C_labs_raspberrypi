/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       PrintArray.c   
|  DATE:          FEB 2019
|  DESCRIPTION:   Prints out an array of integers given the array name and 
|                 array size. 
********************************************************************************/

/*===============================================================================
  FUNCTION:     printArray()
  DESCRIPTION:  Prints out a one dimensional array
  PARAMETERS:   array[], size
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
#include <stdio.h>

void printArray(int array[], int size)
{
	int i = 0;								// Initialize loop count
	printf("Result = {");                   // Print out initial text
	while (i < size)									
	{
		if (i < size - 1)
	   	    printf("%d, ", array[i]);		// Print each array element and comma
	   	else
	   	    printf("%d}\n", array[i]);      // Print out final array element and }
	   	i++;
	}
}

/*===============================================================================
  FUNCTION:     printArray()
  DESCRIPTION:  Prints out a two dimensional array
  PARAMETERS:   array[][3], iSize
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
void print2dArray(int array[][3], int iSize)
/*-------------------------------------------------------------------------------
  Note: You must specify all but the first dimension when passing a multi-
  dimensional array.
  Pointers will let you work around this limitation. (more later...)
-------------------------------------------------------------------------------*/
{
	int i = 0, j = 0, jSize = 3;
	printf("multiDimArray = {{");
	while(i < iSize)
	{
		while(j < jSize)
		{
			if (j < jSize - 1)
			    printf("%d, ", array[i][j]);
			else
			    printf("%d}", array[i][j]);
	        j++;
	    }
	    j = 0;
	    if (i < iSize - 1)
	        printf(", {");
		else
		    printf("}\n");
		i++;
	}
}
