/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab17.c   
|  DATE:          FEB 2019
|  DESCRIPTION:   Open, display and save image with OpenCV. Example with command line arguments.
********************************************************************************/

#include "opencv2/highgui/highgui.hpp" //  required for OpenCV functions
#include <stdio.h>                     // Standard I/O - required for printf() function

 
/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  open, display and save image
  PARAMETERS:   filename
  RETURNS:      -1 - if user give no arguments 
                0 - if success
  REQUIREMENTS: none
===============================================================================*/
int main( int argc, char** argv )
{
    
	printf("Arguments were passed to main():\n");
    for (int i = 0; i<argc; i++) 
		printf("argv[%d] = %s \n", i, argv[i]);
    printf("\n");		
	
	if( argc != 2)
    {
        printf( "Unable to load the image\n"
                "Pass it as the first parameter, e.g.: lab20 typewriter.jpg\n" );
        return -1;
    }
	
    IplImage* image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);  // Loads an image from a file.

    if(image== NULL)                              // Check for invalid input
    {
         printf("Could not open or find the image\n") ;
        return -1;
    }
    

    /* display image in window */
    cvNamedWindow("MyWindow_Name",CV_WINDOW_AUTOSIZE); // Create a window for display.
    cvShowImage("MyWindow_Name",image); // Show our image inside window.
             
	/*int param[2];
    param[0] = CV_IMWRITE_JPEG_QUALITY;
    param[1] = 95;*/	
	cvSaveImage("tmp_typewriter.jpg", image, 0);  // Saves an image to a specified file.	 
                                        
    cvWaitKey(0);    // Wait for a keystroke in the window
	
    cvReleaseImage(&image); // release memory.	
    cvDestroyWindow("MyWindow_Name"); //destroy windows
	
    return 0;
}
