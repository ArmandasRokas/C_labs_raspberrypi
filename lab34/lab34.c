/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab34.c   
|  DATE:          APR 2019
|  DESCRIPTION:   Creating, reading and printing a random-access file
|  source code based on "Fig. 11.11: fig11_11.c", "Fig. 11.12: fig11_12.c",
|                        "Fig. 11.15: fig11_15.c" from "C How to Program, 6/e:"
********************************************************************************/


#include <stdio.h>     // standard I/O - required for input/output function

 
/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  create a file and save data to it, open the file and read the data from it
  PARAMETERS:   none
  RETURNS:      0
  REQUIREMENTS: none
===============================================================================*/
 
// studentData structure definition            
struct studentData 
{                              
	unsigned int idNum; // id number
	char lastName[ 15 ]; //  last name    
	char firstName[ 10 ]; // first name       
};               

int main( void ) 
{ 
	unsigned int i; // counter used to count from 1-100
	// create studentData with default information       
	struct studentData blankStudent = { 0, "", "" }; 
	FILE *cfPtr; // students.dat file pointer

// Creating a random-access file sequentially	
	// fopen opens the file; exits if file cannot be opened
	if (( cfPtr = fopen( "students.dat", "wb" ) ) == NULL) 
	{
		printf( "File could not be opened." );
	}  
	else 
	{ 
		printf( "\n\n--1--Creating a random-access file sequentially\n\n" );
		// output 100 blank records to file                              
		for(i = 1; i <= 100; ++i) 
		{                                   
			fwrite( &blankStudent, sizeof( struct studentData ), 1, cfPtr );
		}
		
		fclose ( cfPtr ); // fclose closes the file
	}

	
// Writing data randomly to a random-access file
    // create studentData with default information
    struct studentData student = { 0, "", "" };
	
	// fopen opens the file; exits if file cannot be opened
	if (( cfPtr = fopen( "students.dat", "rb+" ) ) == NULL) 
	{
		printf( "File could not be opened." );
	}  
	else
	{ 
		printf( "\n\n--2--Writing data randomly to a random-access file\n\n" );
		// require user to specify id number
		printf( "%s", "Enter id number"
		" ( 1 to 100, 0 to end input )\n? " );
		scanf( "%d", &student.idNum );
		
		// user enters information, which is copied into file
		while ( student.idNum != 0 ) 
		{ 
			// user enters last name, first name and balance
			printf( "%s", "Enter lastname, firstname\n? " );
			// set record lastName, firstName
			fscanf( stdin, "%14s%9s", student.lastName, student.firstName );
			// seek position in file to user-specified record   
			fseek( cfPtr, ( student.idNum - 1 ) *              
			sizeof( struct studentData ), SEEK_SET );         
			// write user-specified information in file              
			fwrite( &student, sizeof( struct studentData ), 1, cfPtr );
			// enable user to input another id number
			printf( "%s", "Enter id number\n? " );
			scanf( "%d", &student.idNum );
		}
		
		fclose( cfPtr ); // fclose closes the file
	  }  
	  
	  
// Reading a random access file sequentially
	
	// fopen opens the file; exits if file cannot be opened 
	if ( ( cfPtr = fopen( "students.dat", "rb" ) ) == NULL ) 
	{
		printf( "File could not be opened.\n" );
	}  
	else 
	{ 
		printf( "\n\n--3--Reading a random access file sequentially\n\n" );
		printf( "%-6s%-16s%-11s\n", "Id", "Last Name", "First Name" );

		// read all records from file (until eof) 
		while ( !feof( cfPtr ) ) 
		{ 
			fread( &student, sizeof( struct studentData ), 1, cfPtr );

		// display record
		if ( student.idNum != 0 ) 
		{
			printf( "%-6d%-16s%-11s\n", student.idNum, student.lastName, student.firstName );
		}  

		}  

		fclose( cfPtr ); // fclose closes the file  
	}  

 
	return 0;
}



 


 
