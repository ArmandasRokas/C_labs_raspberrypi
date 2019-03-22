## Mandatory_3	
### Image Processing	

* `Intensity` in grey picture  - color between 0-255, where `255` is white and `0` is black	
* `Number of pixel`- how many pixel is that color (intensity)	
* `HISTOGRAM.SOL` - is just text file of output	
* `CV_RGB2GRAY` - code to convert	

### Questions
* How to check sizeof(image), but not address size. 
### TODO 
* Write to File
* Calculate intensity
  * We know that it only 256 different color. So we can make an array of this size and add counter ++ if the intensity is found. After that just do some print out the values. 

### References	
[Image attributes](https://docs.opencv.org/3.4/d6/d5b/structIplImage.html#ab6315f84a34002b616a187f87999f167)  
[color.hpp repo](https://github.com/opencv/opencv/blob/master/modules/imgproc/src/color.hpp)  
[cvCvtColor docs](https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html#cvtcolor)

### Diverse
#### Testing of creating a local pointer
Exampel show that while increasing a new pointer, it does not effect orginal pointer. So we can safetly increase that. 
```C
	char * myNewLocalImageData = image->imageData;
	printf("Orginal pointer: %p \nMy pointer: %p \n", image->imageData, myNewLocalImageData);  
	imageData++;
	printf("After increasing \nOrginal pointer: %p \nMy pointer: %p \n", image->imageData, myNewLocalImageData);
 	printf("Height: %d \nWidth: %d\n", image->height, image->width);
``` 
### Last pixel in image->imageDate array
```C
image->height*image->width-1 
```

