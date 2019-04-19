#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.h"
#define SIZE 256
void countIntensities(int * intensities, IplImage* image);
int countNumOfDistinctIntensities(int * intensities);
int writeToFile(int * intensities, IplImage* image, int numOfDistinctIntensities);

int main(int argc, char** argv)
{
	printf("Arguments were passed to main():\n");
	for(int i=0; i<argc; i++){
		printf("argv[%d] = %s \n", i , argv[i]);
	}	
	
	if( argc != 2)
    {
        printf( "Unable to load the image\n" );
        return -1;
    }
    
    IplImage* color_image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR); 
    if(color_image == NULL){
		printf("Unable to load the image\n");
		return -1;
	}
    IplImage* image = cvCreateImage(cvGetSize(color_image), 8, 1);
    cvCvtColor(color_image, image, CV_RGB2GRAY ); 

	int intensities[SIZE] = {0};
	countIntensities(intensities, image);
	int numOfDistinctIntensities = countNumOfDistinctIntensities(intensities);
	writeToFile(intensities, image, numOfDistinctIntensities);
	
	return 0;
}

void countIntensities(int * intensities, IplImage* image){
	int numTotalPixels = image->height*image->width;
    
    for(int i = 0; i < numTotalPixels; i++){
			int currIntensity = image->imageData[i];
			intensities[currIntensity]++; // uses current intensity value as an index 
	}
}
int countNumOfDistinctIntensities(int * intensities){
	int numOfDistinctIntensities = 0;
	for(int i = 0; i < SIZE; i++){
		if(intensities[i] != 0){
			numOfDistinctIntensities++;
		}
	}
	return numOfDistinctIntensities;
}

int writeToFile(int * intensities, IplImage* image, int numOfDistinctIntensities){
	
	FILE * fptr;
	fptr = fopen("HISTOGRAM.SOL", "w");
	if(fptr == NULL){
			printf("Could not open HISTOGRAM.SOL\n");
			return -1;
	}
	
	fprintf(fptr, "%d\n", numOfDistinctIntensities);   // Writes distinct intensities		    
	fprintf(fptr, "%dx%d\n", image->width, image->height); // Writes resolution
	
    for(int i = 0; i < SIZE; i++){
		if(intensities[i] != 0){
			fprintf(fptr, "%d %d\n", i, intensities[i]); // Writes intensities
		}
	}
	fclose(fptr);
	return 1;
}
