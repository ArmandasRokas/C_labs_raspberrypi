#include "opencv2/highgui/highgui.hpp" // required for OpenCV functions
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>                     // standard I/O - required for printf() function
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#define THRESHOLD 50
#define DEBUG 1

int compareImages(IplImage * image1, IplImage * image2);
void logTxt(struct tm * timeinfo);
void logJpg(struct tm * timeinfo, IplImage * image);


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

	time_t prevTime;
	time_t currTime;
    struct tm * timeinfo;
    
    IplImage* currFrame = 0;
	IplImage* prevFrame = 0;

	// Read the video stream
	capture = cvCaptureFromCAM(0);
	//cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 640 );
	//cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 480 );
	//cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
	
	//cvSaveImage("image_test.jpg", image_test, 0);
	
	if( capture )
	{

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
				
				time(&currTime);
				if (difftime(currTime, prevTime) > 4){
					timeinfo = localtime(&currTime);
					prevTime = currTime;
					logTxt(timeinfo);
					logJpg(timeinfo, currFrame);
				}
			}
			
			#if DEBUG
			printf("Scanning\n");
			#endif
			

		//	cvShowImage( "Video", currFrame );
			
			// Press 'c' to escape
			//c = cvWaitKey(100);
			//if( (char)c == 'c' ) { break; }		
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
	  if(gray_res->imageData[i] > THRESHOLD){ // manual Thresholding
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

/*******************************
 * Logs the movement time to text files
 ******************************/

void logTxt(struct tm * timeinfo){
		#if DEBUG
			printf("In log txt\n");
		#endif
		
        static const char mon_name[][4] = {
        "JAN", "FEB", "MAR", "APR","MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
      // time_t rawtime;
      //  struct tm * timeinfo;
       // time(&rawtime);
      //  timeinfo = localtime(&rawtime);

        FILE * cfPtr;
        char * file_name = (char *) malloc(15*sizeof(char));
        int year = timeinfo->tm_year + 1900;
        sprintf(file_name, "log%d%s.txt", year, mon_name[timeinfo->tm_mon]);

        if ((cfPtr = fopen(file_name, "a+")) == NULL){
                printf("File could not be opened");
                exit(1);
        }

        fprintf(cfPtr, "%d-%02d-%02d %02d:%02d:%02d\n",
                        year,
                        timeinfo->tm_mon+1,
                        timeinfo->tm_mday,
                        timeinfo->tm_hour,
                        timeinfo->tm_min,
                        timeinfo->tm_sec);
        //free(timeinfo); gives: free(): invalid pointer: https://stackoverflow.com/questions/20297524/c-free-invalid-pointer
        free(file_name);
        fclose(cfPtr);
        //free(rawtime); //gives: attempt to free a non-heap object
}
void logJpg(struct tm * timeinfo, IplImage * image){

	CvScalar color;
	CvFont base_font;
	color = CV_RGB(36,0,250); // blue
	cvInitFont( &base_font, CV_FONT_HERSHEY_SIMPLEX, 1.5, 1.5, 0, 1, 8);
	
	char * currTime = (char *) malloc(19*sizeof(char));
	sprintf(currTime, "%d-%02d-%02d %02d:%02d:%02d",
                        timeinfo->tm_year+1900,
                        timeinfo->tm_mon+1,
                        timeinfo->tm_mday,
                        timeinfo->tm_hour,
                        timeinfo->tm_min,
                        timeinfo->tm_sec);

	IplImage * edited_image = cvCloneImage(image); // clone image to not affect the original image
	cvPutText(edited_image, currTime, cvPoint(10, 400), &base_font, color);
	
	char * file_name = (char *) malloc(23*sizeof(char));
	sprintf(file_name, "%s.jpg", currTime);
	
	cvSaveImage(file_name, edited_image, 0);
	
	cvReleaseImage(&edited_image);
	free(currTime);
	free(file_name);
}
