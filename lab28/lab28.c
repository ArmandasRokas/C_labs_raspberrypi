/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab28.c   
|  DATE:          MAR 2019
|  DESCRIPTION:   Capture video
********************************************************************************/
#include "opencv2/highgui/highgui.hpp" //  required for OpenCV functions

int main()
{
/*	CvCapture* capture;
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
*/

	IplImage* image1 = cvLoadImage("image.jpg", CV_LOAD_IMAGE_COLOR);  // Loads an image from a file.
	IplImage* image2 = cvLoadImage("image1.jpg", CV_LOAD_IMAGE_COLOR);  // Loads an image from a file.

    if(image1== NULL) // Check for invalid input
    {
        printf("Could not open or find the image1\n") ;
        return -1;
    }
    if(image2== NULL)  // Check for invalid input
    {
        printf("Could not open or find the image2\n") ;
        return -1;
    }
    
    
	return 0;
}
