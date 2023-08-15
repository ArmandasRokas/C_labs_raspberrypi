//  lab1-GPIO
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

//#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd; // A file descriptor, which is an integer value used to identify an open file.  
void *gpio_map;

// I/O access
/*
	unsigned *, in this case, it's a pointer to an unsigned integer,
	 which is often used when working with hardware registers.
	 This type of construct is often used when dealing with memory-mapped 
	 hardware registers in embedded programming or other situations where
	 memory values can change due to external events. 
*/
volatile unsigned *gpio;  


/*
	GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
	It may be used in your code much like a function. The benefit of using macro
	like this is that it doesn't care what data type the parameter has.
	The disadvantage is that the code will be compiled inline and take up more
	space than a function call, if it used frequently. 
*/ 
// #define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

void setup_io();

// TODO: write the function as normal
// TODO: then try to output memory addresses and bank and try to see memory addresses and calculated values.

//TODO: Try to write this manually. Without the functions INP_GPIO and OUT_GPIO
// since it works just as helper functions for this specific case.
// so it's like using a library. 

void INP_GPIO_transformed_function(int g) {
	int bank = g / 10; // But from where I should know about these banks
	int shift = (g % 10) * 3; // Result is 15.  Note that,  "3" is here because each GPIO is represented by 3 bits.
	unsigned int bitmask = ~(7 << shift); //  11111111111111  000111111111111111  https://bit-calculator.com/bit-shift-calculator
										  //      
	printf("gpio[bank]: %p", gpio[bank]);  

	gpio[bank] &= bitmask;  // So it puts 0, where we can, and 1's all other places, since we dont want to mess up with other, if there were 1's in the first hand. 

/*
	In this particular example, if we need to set pin 25 as output
	From table 6-4 - GPIO Alternate function select register 2 (0x7E30 0008)
	Bit 17-15  to 001. 
*/
}

void INP_GPIO_PIN_25()
{  
	// gpio[2] according to Table 6-2 following with  6.1 Register View
	gpio[2] &= ~(7 << 15); // ~7 will give 000.  "15" is according to Table 6-4.  
}

void OUT_GPIO_PIN_25()
{
	gpio[2] |= 1 << 15;
}

int main(int argc, char **argv)
{
	int g,rep;

	// Set up gpio pointer for direct register access
	setup_io();

	/*
		Switch GPIO 25 to output mode
		GPIO 25 is the green field in Raspberry Pi datasheet
		That is the pin 25, but just in the position of 22.
	*/ 
	g = 25;
	// INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
	// OUT_GPIO(g);

	INP_GPIO_PIN_25();
	OUT_GPIO_PIN_25();


	for (rep=0; rep<10; rep++)
	{
	//    GPIO_SET = 1<<g;
		*(gpio+7) = 1 << g;
	   sleep(1);
 
	//    GPIO_CLR = 1<<g;
	   *(gpio+10) = 1 << g;
	   sleep(1);
	}

	return 0;

} // main


//
// Set up a memory regions to access GPIO
//
void setup_io()
{
   /* 
		The file "/dev/mem" provides access to the physical memory
		of the computer, allowing programs to read and write directly
		to physical memory addresses.
		
		Open is a system call that tries to open the file.
			- O_RDWR - flag indicates that the file should be opened for both
				reading and writing.
			- O_SYNC flag requests synchronous I/O operations, which means
				that the program will wait for each write operation to 
				complete before proceeding.  
		
   */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* 
		`mmap` function map a portion of memory from the "/dev/mem" file
		into the program's address space. 
		This is often done when dealing with memory-mapped peripherals, such
		as GPIO registers on a hardware devices
		Memory-mapped I/O provides a way to access hardware registers as if
		they were ordinary memory locations. 
    */
   gpio_map = mmap(
      NULL,             //Any address in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writing to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }
	/*
		!Always use volatile pointer!
		The volatile keyword indicates to the compiler tht the memory being
		accessed through this pointer may change unexpectedly, such as 
		through hardware interactions. 
		This prevents the compiler from optimizing away certain reads or
		writes to memory locations that could be modified externally. 
	*/
   gpio = (volatile unsigned *)gpio_map;
}
