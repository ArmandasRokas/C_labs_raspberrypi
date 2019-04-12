#include "opencv2/highgui/highgui.hpp" // required for OpenCV functions
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>                     // standard I/O - required for printf() function
#include <unistd.h>
#define DEBUG 1

int compareImages(IplImage * image1, IplImage * image2);

/******************************
 * Remember before start: sudo modprobe bcm2835-v4l2
 * 
 * ***************************/
int main()
{
	#if DEBUG
		printf("Program is started\n");
	#endif
  	CvCapture* capture;
	//int c;

	

	// Read the video stream
	capture = cvCaptureFromCAM(0);
	//cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 640 );
	//cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 480 );
	//cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
	
	//cvSaveImage("image_test.jpg", image_test, 0);
	
	if( capture )
	{
		IplImage* currFrame = 0;
		IplImage* prevFrame = 0;
		currFrame = cvQueryFrame( capture );
		prevFrame = cvCloneImage(currFrame); // have to clone in order to have older image
		while(1)
		{
			currFrame = cvQueryFrame(capture);
			//IplImage* currFrame = cvQueryFrame( capture );
			
			
		//	if(!currFrame){
			//	break;
		//	}
		//	sleep(1);
			//IplImage* prevFrame = cvCloneImage(currFrame);
		//	sleep(1);
		//	currFrame = cvQueryFrame( capture );
	
			if(compareImages(currFrame,prevFrame)){
				#if DEBUG
				printf("Found movement\n");
				#endif
			}
			
			#if DEBUG
			printf("Scanning\n");
			#endif
			//sleep(1);

		//	cvShowImage( "Video", currFrame );
			
			// Press 'c' to escape
		//	c = cvWaitKey(100);
		//	if( (char)c == 'c' ) { break; }		
			cvCopy(currFrame, prevFrame, NULL);
		}
	} else {
		printf("Error capturing camera\n");
	}
	cvReleaseCapture( &capture ); // release memory.	
    cvDestroyWindow("Video"); //destroy windows
    return 0;
    
}


/****************************************************
 * Return 1, if there are any differences in pictures
 * Return 0, if there are no differences
 * ***************************************************/
int compareImages(IplImage * image1, IplImage * image2){
	//cvSaveImage("image_test1.jpg", image1, 0);
	//cvSaveImage("image_test2.jpg", image2, 0);
	IplImage* res = cvCreateImage(cvGetSize(image1), 8, 3);
	
	cvAbsDiff(image1,image2,res);
    
    IplImage* gray_res = cvCreateImage(cvGetSize(res), 8, 1);
    cvCvtColor(res, gray_res, CV_RGB2GRAY );
	int count = 0;
	for(int i = 0; i < res->height*res->width;i++){
	  if(gray_res->imageData[i] > 50){
		count++;
	  }
	}
	cvReleaseImage(&res);   // OutOfMemoryError without releases
	cvReleaseImage(&gray_res);
	if(count > 10){ 
		return 1;
	} else{
		return 0;
	}
	
}
