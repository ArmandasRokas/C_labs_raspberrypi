/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab28.c   
|  DATE:          MAR 2019
|  DESCRIPTION:   Capture video and display text and time on stream
********************************************************************************/

#include "opencv2/highgui/highgui.hpp" //  required for OpenCV functions
#include <stdio.h>                     // Standard I/O - required for printf() function
#include <time.h>

 

int main()
{
	CvCapture* capture;
	CvScalar color;
	CvFont base_font;
	CvFont time_font;	
	time_t curtime;
	int c;

	// Read the video stream
	capture = cvCaptureFromCAM( 0 );
	cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
	
	//  init some text 
	color = CV_RGB(235,235,235); // gray
	// Initializes font structure
	cvInitFont( &base_font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 4, 8);

	//  init time text 
	// Initializes font structure
	cvInitFont( &time_font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 2, 8);	
	
	if( capture )
	{
		while(1)
		{		 
			IplImage* frame = cvQueryFrame( capture );
			if( !frame )
				break;
			 			
			//Draws a text string
			cvPutText(frame, "View from my camera", cvPoint( 10, 440 ), &base_font, color);
			
			time(&curtime);
			//Draws a time string			
			cvPutText(frame, strtok(ctime(&curtime), "\n"), cvPoint( 10, 20 ), &time_font, color);	
			
			cvShowImage( "Video", frame );
			
			// Press 'c' to escape
			c = cvWaitKey(10);
			if( (char)c == 'c' ) { break; }
		}
	}
	
	cvReleaseCapture( &capture ); // release memory.	
    cvDestroyWindow("Video"); //destroy windows
	
	return 0;
}

