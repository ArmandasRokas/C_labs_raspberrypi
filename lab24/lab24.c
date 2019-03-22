/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab24.c   
|  DATE:          MAR 2019
|  DESCRIPTION:   
********************************************************************************/

#include "opencv2/highgui/highgui.hpp" //  required for OpenCV functions
#include <stdio.h>                     // Standard I/O - required for printf() function

 
/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  draws a line, a circle, a rectangle, put text and save image
  PARAMETERS:   filename
  RETURNS:      0
  REQUIREMENTS: none
===============================================================================*/
int main( void)
{
	CvScalar color;
	CvScalar bkgnd_color;
	CvFont base_font;
	
	// Creates an image header and allocates the image data
	IplImage* image = cvCreateImage(cvSize(640, 480), 8, 3);

	// you can set any color
	bkgnd_color = CV_RGB(10,10,10);
	cvSet(image, bkgnd_color, 0);
	
	// black empty images
	//cvZero(image);   
       
// Drawing a line 
	color = CV_RGB(255,70,0); // red
	// Draw a line
	cvLine( image, cvPoint( 1, 1 ), cvPoint( 70, 50), color, 2, 8, 0 );
    
	
/*  Drawing a rectangle */  
	// Draw a rectangle ( 5th argument is not -ve)
	color = CV_RGB(82,216,34); // green
	cvRectangle( image, cvPoint( 140, 100 ), cvPoint( 160, 140), color, +1, 4, 0 );
	
	color = CV_RGB(250,250,0); // yellow
	// Draw a filled rectangle ( 5th argument is -ve)
	cvRectangle( image, cvPoint( 140, 20 ), cvPoint( 160, 60), color, -1, 8, 0 );
	
/*  Drawing a circle */  
    color = CV_RGB(36,0,250); // blue
	// Draw a circle 
 	cvCircle(image, cvPoint( 360, 280 ), 64.0, color, 1, 8, 0 );

/*  Putting text */  
	color = CV_RGB(235,235,235); // gray
    // Initializes font structure
	cvInitFont( &base_font, CV_FONT_HERSHEY_SIMPLEX, 1.5, 1.5, 0, 1, 8);
	//Draws a text string
	cvPutText(image, "My amazing text", cvPoint( 10, 400 ), &base_font, color);
 
  
/* Display image in window */
    cvNamedWindow("MyDrawing",CV_WINDOW_AUTOSIZE); // Create a window for display.
    cvShowImage("MyDrawing",image); // Show our image inside window
	
	cvSaveImage("my_drawing.jpg", image, 0);  // Saves an image to a specified file.	
	
	cvWaitKey(0);    // Wait for a keystroke in the window

    cvReleaseImage(&image); // release memory.	
    cvDestroyWindow("MyDrawing"); //destroy windows

 
	return 0;	
}
