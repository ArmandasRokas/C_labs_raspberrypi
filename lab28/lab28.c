/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab28.c   
|  DATE:          MAR 2019
|  DESCRIPTION:   Capture video
********************************************************************************/
#include "opencv2/highgui/highgui.hpp" //  required for OpenCV functions

int main()
{
	CvCapture* capture;
	int c;

	// Read the video stream
	capture = cvCaptureFromCAM( 0 );
	cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
	
	if( capture )
	{
		while(1)
		{
			IplImage* frame = cvQueryFrame( capture );
			if( !frame )
				break;

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