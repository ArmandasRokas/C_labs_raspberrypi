## Questions 
- Er det menning at selvom der blev taget to billede lige efter hinannden uden at der var bevægelse, at der ikke er éns billeder.
Dvs. Når jeg laver cvAbsDiff og tjekker intensities, så alle mere er end nul. Så skal jeg selv vurdere hvor meget skal jeg ignorere? 
Dvs. hvis intensity mere end 50, så skal jeg betragte som forskel.  

## Errors
### Comparing two frames
```
OpenCV Error: Insufficient memory (Failed to allocate 307200 bytes) in OutOfMemoryError, file /build/opencv-U1UwfN/opencv-2.4.9.1+dfsg1/modules/core/src/alloc.cpp, line 52
terminate called after throwing an instance of 'cv::Exception'
  what():  /build/opencv-U1UwfN/opencv-2.4.9.1+dfsg1/modules/core/src/alloc.cpp:52: error: (-4) Failed to allocate 307200 bytes in function OutOfMemoryError

Aborted
```
