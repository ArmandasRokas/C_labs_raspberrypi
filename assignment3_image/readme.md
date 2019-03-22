## Mandatory_3	
### Image Processing	

* `Intensity` in grey picture  - color between 0-255, where `255` is white and `0` is black	
* `Number of pixel`- how many pixel is that color (intensity)	
* `HISTOGRAM.SOL` - is just text file of output	
* `CV_RGB2GRAY` - code to convert	

### Questions

### TODO 
* Write to File
* Calculate intensity
  * We know that it only 256 different color. So we can make an array of this size and add counter ++ if the intensity is found. After that just do some print out the values. 

### References	
[Image attributes](https://docs.opencv.org/3.4/d6/d5b/structIplImage.html#ab6315f84a34002b616a187f87999f167)  
[color.hpp repo](https://github.com/opencv/opencv/blob/master/modules/imgproc/src/color.hpp)  
[cvCvtColor docs](https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html#cvtcolor)

### Diverse
#### Testing of creating local pointer
```C
	char * imageData = image->imageData;
	printf("Orginal pointer: %p \nMy pointer: %p \n", image->imageData, imageData);  
	imageData++;
	printf("After increasing\n Orginal pointer: %p \nMy pointer: %p \n", image->imageData, imageData);
 	printf("Height: %d \nWidth: %d\n", image->height, image->width);
``` 

dsds
