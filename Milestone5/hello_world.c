/*
 * Milestone 5:
 *
 * Take images and brightness and contrast values from QT over RS-232
 * interface and output the resulting pictures to the VGA interface
 *
 */

#include <stdio.h>

void SetSourceImage()
{
	// TODO: Write to source image buffer as well as the monitor via VGA
	// First byte was read, everything that follows starts the data
	volatile short * pixel_buffer = (short *) 0x08000000; // Pixel buffer
	int x = 0;	// x and y offset with top left as 0,0
	int y = 0;
	int offest = 0;
	int red, green, blue;
	unsigned short pixelColor = 0;

	/*
	 * Image will be sent with bottom left being first at 0,0 and a row at a time
	 */
	printf("Reading and displaying image");
	// keep reading the buffer
	// Variables for the serial communication
		volatile int * SerialDataRegister = (int *) 0x10001010;	// Data register of serial port
		int regValue = 0;
		int Shade = 0;
		int RVALID = 0;

	while(y < 240) // loop until the picture is filled
	{
		while(x < 320) // loop until the row is filled
		{
			regValue = *(SerialDataRegister);
			RVALID = regValue & 0x00008000;
			Shade = regValue & 0x000000ff;
			if (RVALID) // this byte is good, use it
			{
				// calculate color based on shade given over serial
				// red and blue are 5 bits, green is 6.
				// no need to bitmask because shade already was
				blue = red = Shade >> 3;
				green = Shade >> 2;
				pixelColor = (red << 11) + (green << 5) + (blue);
				// calculate offset based on pixel position
				offset = (y << 9) + (x << 1);
				*(pixel_buffer + offset) = pixelColor;
				x = x + 1;
			}
		}
		x = 0;
		y = y + 1;
	}
}

void setOverlayImage()
{
	// TDOD: implement this to dump image in memory
}

void adjustBrightness(int value)
{
	// TODO: this
}

void adjustBrightness(int value)
{
	// TODO: this
}

void updateVGA()
{
	// TODO: this, code is in the source image function
}

int main()
{
	printf("Hello from Nios II!\n");

	printf("Starting");
	// Variables for the serial communication
	volatile int * SerialDataRegister = (int *) 0x10001010;	// Data register of serial port
	int regValue = 0;
	int receivedValue = 0;
	int RVALID = 0;


	while (1)
	{
		// Get the digit from the serial communication:
		/*
		 * Communication Protocol:
		 * First byte is the tag, bits 7:0 is the data type
		 * 		0 is null
		 * 		1 is Brightness
		 * 		2 is contrast
		 * 		3 is source image
		 * 		4 is overlay image
		 * 		5 - 255 are null
		 *
		 * The following byte will be data until the data stream stops
		 * 		(This may have to be changed if the connection is choppy)
		 * 		Pictures should be size of 320x240
		 */
		regValue = *(SerialDataRegister);
		RVALID = regValue & 0x00008000;
		receivedValue = regValue & 0x000000ff;
		if (RVALID)
		{
			switch(receivedValue) {
			case 1:
				// Brightness number
				break;
			case 2:
				// Contrast Number
				break;
			case 3:
				// Source Image
				setSourceImage();
				break;
			case 4:
				// Overlay Image
				break;
			default:
				break;
			}
		}
	}

	return 0;
}
