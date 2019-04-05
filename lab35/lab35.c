/********************************************************************************
|  CLASS:         62409 C programming for Java programmers
|  PROGRAM:       lab35.c   
|  DATE:          APR 2019
|  DESCRIPTION:   Operations on images using bit-wise inversion and using function cvAbsDiff()
********************************************************************************/

#include "opencv2/highgui/highgui.hpp" // required for OpenCV functions
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>                     // standard I/O - required for printf() function

 
/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  Operations on images using bit-wise inversion AND, OR, XOR and NOT. 
                Calculates the per-element absolute difference between two arrays.
  PARAMETERS:   none
  RETURNS:      -1 - if no images
                0 - if success
  REQUIREMENTS: none
===============================================================================*/
int main( int argc, char** argv )
{
	
    IplImage* image1 = cvLoadImage("photo-1.jpg", CV_LOAD_IMAGE_COLOR);  // Loads an image from a file.
	IplImage* image2 = cvLoadImage("photo-2.jpg", CV_LOAD_IMAGE_COLOR);  // Loads an image from a file.

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
  //  printf("%d %d", image1->height, image1->width);

    IplImage* res = cvCreateImage(cvGetSize(image1), 8, 3);
	//IplImage* res = cvCreateImage(cvSize(*, *), 8, 3);
	cvAbsDiff(image1,image2,res);
	//cvAnd(image1, image2, res,  NULL);
	//cvNot(image1, res);
	//cvOr(image1, image2, res,  NULL);
	//cvXor(image1, image2, res,  NULL);
	// use function cvAbsDiff  //Calculates the per-element absolute difference between two arrays
	
    // display image in window 
    
    IplImage* gray_res = cvCreateImage(cvGetSize(res), 8, 1);
    cvCvtColor(res, gray_res, CV_RGB2GRAY );
  int count = 0;
  int pixels = 0;
  for(int i = 0; i < res->height*res->width;i++){
	  pixels++;
	  if(gray_res->imageData[i] > 0){
		count++;
	  }
  }
  printf("Num of total pixels: %d\n", pixels);
  printf("Num of different pixels: %d\n", count);
   // printf("Image intesity: %d",res->imageData[10000]);
    
    cvNamedWindow("ResultWindow",CV_WINDOW_AUTOSIZE); // Create a window for display.
    cvShowImage("ResultWindow",res); // Show our image inside window.
             
                                         
    cvWaitKey(0);    // Wait for a keystroke in the window
	
    cvReleaseImage(&res); // release memory.	
    cvDestroyWindow("ResultWindow"); //destroy windows
    cvReleaseImage(&image1); // release memory.	
    cvReleaseImage(&image2); // release memory.	  
	
    return 0;
}
