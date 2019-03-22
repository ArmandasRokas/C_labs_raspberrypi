#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


int main(int argc, char** argv)
{
	printf("Arguments were passed to main():\n");
	for(int i=0; i<argc; i++){
		printf("argv[%d] = %s \n", i , argv[i]);
	}	
	
	if( argc != 2)
    {
        printf( "Unable to load the image\n"
                "Pass it as the first parameter, e.g.: lab20 typewriter.jpg\n" );
        return -1;
    }
    
    
    
 //   IplImage* image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
 //   IplImage* image2 = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    IplImage* image = cvLoadImage(argv[1], 0);
    
    
//    cvCvtColor(image, image2, CV_8U);
    cvSaveImage("test_grey.jpg", image, 0);
    
    printf("Height: %d \n Width: %d\n", image->height, image->width);
      
    
	
	return 0;
}