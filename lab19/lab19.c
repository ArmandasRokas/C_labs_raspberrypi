/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab19.c   
|  DATE:          FEB 2019
|  DESCRIPTION:   Examples of using functions to manipulate C strings
********************************************************************************/

#include <stdio.h>
#include <string.h>

int main()
{
	int i, j = 0, k = 0;
	char str[100], key[20];
	char str1[10][20];
	char *tokenPtr;
	int tokens=0;
	
	printf("enter string:");
	scanf("%[^\n]s",str);
	
	/* Converts the string into 2D array */
	for (i = 0; str[i]!= '\0'; i++)
	{
		if (str[i]==' ')
		{
			str1[k][j] = '\0';
			k++;
			j = 0;
		}
		else
		{
			str1[k][j] = str[i];
			j++;
		}
	}
	
	str1[k][j] = '\0';
	printf("enter key:");
	scanf("%s", key);
	/* Compares the string with given word */
	for (i = 0;i < k + 1; i++)
	{
		//### Your Code Here ### 
		//if (strcmp(?????) == 0)	
		{
			for (j = i; j < k + 1; j++)
				//### Your Code Here ###  	
                //strcpy(???)
			k--;
		}
	}
	
	for (i = 0;i < k + 1; i++)
	{
		printf("%s ", str1[i]);
	}
	//counting tokens
	tokenPtr = strtok( str, " ");
	++tokens;
	/* while tokenPtr does not equal NULL */
	while ( tokenPtr )
	{
		++tokens;
		tokenPtr = strtok(NULL, " " ); /* get next token */
	}
	
	printf("\nTotal number of words in the original line: %d\n", tokens-1);
	printf("\nTotal number of words in the present line: %d\n", i);
}
