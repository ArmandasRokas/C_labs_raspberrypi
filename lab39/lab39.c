/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab39.c   
|  DATE:          APR 2019
|  DESCRIPTION:   Operations on images - Threshold operation 
|  program code based on the source code from:  
|  https://docs.opencv.org/2.4/doc/tutorials/imgproc/threshold/threshold.html 
********************************************************************************/

#include "opencv2/highgui/highgui.hpp" // required for OpenCV functions
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>                     // standard I/O - required for printf() function
#include <stdlib.h>

// Global variables
int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

IplImage* src;
IplImage* src_gray;
IplImage* dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

// Function headers
static void Threshold_Demo( int a);
 
/*===============================================================================
  FUNCTION:     main()
===============================================================================*/
int main( int argc, char** argv )
{

	src = cvLoadImage( "dog.jpg", CV_LOAD_IMAGE_COLOR ); // Loads an image from a file
    
	if(src== NULL) // Check for invalid input
    {
        printf("Could not open or find the image1\n") ;
        return -1;
    }
	
	src_gray = cvCreateImage(cvGetSize(src), 8, 1);
	dst = cvCreateImage(cvGetSize(src), 8, 1);
	
	// Convert the image to Gray
	cvCvtColor( src, src_gray, CV_BGR2GRAY );
  
	// Create a window to display results
	cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
	//cvShowImage( window_name, src_gray ); // Show our image inside window.
 
	// Create Trackbar to choose type of Threshold
	cvCreateTrackbar( trackbar_type, 
					  window_name, &threshold_type, 
					  max_type, Threshold_Demo );
					  
	cvCreateTrackbar( trackbar_value,
					  window_name, &threshold_value,
					  max_value, Threshold_Demo );
				  
	
	// Call the function to initialize
	Threshold_Demo( 0 );
	
	// Wait until user finishes program
	while(1)
	{
		int c;
		c = cvWaitKey( 20 ); // Wait for a keystroke in the window
		if( (char)c == 27 )
		  { break; }
	}	
  	
    cvReleaseImage(&src); // release memory.	
	cvReleaseImage(&src_gray); // release memory.	
	cvReleaseImage(&dst); // release memory.	
    cvDestroyWindow(window_name); //destroy windows

	
    return 0;
}


/*===============================================================================
  FUNCTION:     Threshold_Demo
===============================================================================*/
static void Threshold_Demo( int a)
{
	/* 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
	*/
	(void)a;
	cvThreshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

	cvShowImage( window_name, dst ); // Show our image inside window.
}
