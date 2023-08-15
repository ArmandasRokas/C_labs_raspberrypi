//  lab2-GPIO
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program. The program uses the code contained 
//  on the website https://elinux.org/RPi_GPIO_Code_Samples#Direct_register_access" provided by Dom and Gert



// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>  // to mmap function
#include <unistd.h>
#include <stdint.h>

//#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

void setup_io();


int main(int argc, char **argv)
{
    printf("Program starts.\n");
	int gLED = 25;  // GPIO 25 - for diode 
	int gSwitch = 23; // GPIO 23 - for switch

	// Set up gpio pointer for direct register access
	setup_io();

	// Set GPIO pin 25 to output
	INP_GPIO(gLED); // must use INP_GPIO before we can use OUT_GPIO
	OUT_GPIO(gLED);

	INP_GPIO(gSwitch); // Set GPIO pin 25 to input
 
	/* 
		Enable Pull Up control
		In our case, one end of the switch is connected to the ground 
		and the other to the GPIO pins, and you have to pull up the GPIO.
		Then the GPIO will normally read the high state and read the low
		level after closing the switch (button pressed).
		Each GPIO pin has configurable pull-up and pull-down resistors.
		If we ommit this setting, none of the resistors will be turned on.
		This leaves a variable inout, which means you can not rely on its 
		value and it will drift between high and low depending on what you
		pick up on the path of electrical noise. 

		The pull-up means it pulls up the pin to 5V when nothing else happens. 
		When the button is pushed down now there is path from other side 
		of the resistor to ground. So:
			!High (5V), when it's not pressed
			!Low (0V), when it's pressed
		References:
			https://www.youtube.com/watch?v=wxjerCHCEMg
			https://www.youtube.com/watch?v=u3Xiy2DVnI4
			https://grantwinney.com/using-pullup-and-pulldown-resistors-on-the-raspberry-pi/
		

		Pull-up:
			- Pulls up to 5V 
			- Input pin -> Resistor -> Power supply
		Pull-down:
			- Pulls down to 0V
			- Input pin -> Resistor -> Power supply	


		Button example:

				A ------------- D	5V (Pull-down) / Ground (Pull-up)
						|
						  |
						|
		Input	B ------------- C	Resistor  ->  Ground (Pull-down) / 5V (Pull-up)  
		
		References: 
			https://www.youtube.com/watch?v=5vnW4U5Vj0k

	*/
	GPIO_PULL = 1 < 1; //TODO: Try to build the board without the pull up.
	usleep(1);
	GPIO_PULLCLK0 = 1 < gSwitch; // Select GPIO pin 23. GPIO Pin Pull-up/down Enable Clock 0
	usleep(1);
	
	unsigned int val = 10; // value used in the while loop so that the program runs for some time
	
 
	printf("Before while");
    while(val > 0) 
	{
        usleep(200000); //delay for 0.2 seconds
     	unsigned int pin_value = *(gpio + 13) >> gSwitch; // read pin state (no debounce to make code more readable)
		printf("%u", pin_value &= 1);
        if (pin_value &= 1 == 1)
		{
			printf("Button pushed"); // print message
			*(gpio + 7) |= 1 << gLED; // turn on and turn off the diode.		
		} else {
			*(gpio + 10) |= 1 << gLED; 
		}
    }		
	
	
	return 0;

} // main


//
// Set up a memory regions to access GPIO
//
void setup_io()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;


} // setup_io