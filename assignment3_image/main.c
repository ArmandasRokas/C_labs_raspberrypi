#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 256

int main(int argc, char** argv)
{
	FILE * fptr;
	fptr = fopen("HISTOGRAM.SOL", "w");
	if(fptr == NULL){
			printf("File does not exists \n");
			return -1;
	}

	int intensities[SIZE] = {0};
	int numOfDistinctIntensities;
	
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
    
    IplImage* image = cvLoadImage(argv[1], 0);
    int numTotalPixels = image->height*image->width;
    
    for(int i = 0; i < numTotalPixels; i++){
			int currIntensity = image->imageData[i];
			intensities[currIntensity]++; // uses current intensity value as an index 
	}

	// Counts distinct intensities
	for(int i = 0; i < SIZE; i++){
		if(intensities[i] != 0){
			numOfDistinctIntensities++;
		}
	}
	fprintf(fptr, "%d\n", numOfDistinctIntensities);   // Writes distinct intensities		    
	fprintf(fptr, "%dx%d\n", image->width, image->height); // Writes resolution
	
    for(int i = 0; i < SIZE; i++){
		if(intensities[i] != 0){
			fprintf(fptr, "%d %d\n", i, intensities[i]); // Writes intensities
		}
	}
	fclose(fptr);
    
	return 0;
}
