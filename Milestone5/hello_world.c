/*
 * Milestone 5:
 *
 * Take images and brightness and contrast values from QT over RS-232
 * interface and output the resulting pictures to the VGA interface
 * 
 * NIOS II memory:
 * SDRAM from 0x00000000 to 0x07ffffff
 * SRAM from 0x08000000 to 0x081fffff
 * On-Chip Memory from 0x09000000 to 0x09001fff
 * SD card from 0x0b000000 to 0x0b0001ff
 * Flash from 0x0c000000 to 0x0c7fffff
 * Parallel ports (peripherials) from 0x10000000 and up
 */

#include <stdio.h>

#define OVERLAY_IMAGE_STOARGE_MEM_LOC 0x04100000
#define SOURCE_IMAGE_STOARGE_MEM_LOC 0x04000000
#define PIXEL_BUFFER_ADDRESS 0x08000000
#define SERIAL_DATA_REGISTER 0x10001010

int brightness;
double contrast;

void updateVGA()
{
	// Memory addresses
	volatile short * pixel_buffer = (short *) PIXEL_BUFFER_ADDRESS; // Pixel buffer
	short * ImageStoarge = (short *) SOURCE_IMAGE_STOARGE_MEM_LOC; // mock Pixel buffer to store source image
	short * OverlayStoarge = (short *) SOURCE_IMAGE_STOARGE_MEM_LOC; // mock Pixel buffer to store overlay image
	//Variables
	int shade, red, yellow, blue, pixelColor;
	int x = 0;	// x and y offset with top left as 0,0
	int y = 239;
	int offest = 0;

	printf("Modifying and displaying image\n");
	while(y >= 0) // loop until the picture is filled
	{
		while(x < 320) // loop until the row is filled
		{
			offset = (y << 9) + (x << 1); //memory offset for this pixel
			//First check overlay, if overlay is black, print white to screen
			if( *(OverlayStoarge + offset) = 0 )
			{
				//overlay is black, just print white
				shade = 255;
			}
			else
			{
				//overlay is white so adjust brightness and contrast
				shade = contrast * (*(ImageStoarge + offset)) + brightness;
			}

			// Calculate colors from shade
			blue = red = shade >> 3;
			green = shade >> 2;
			pixelColor = (red << 11) + (green << 5) + (blue);
			// Update the image buffer
			*(pixel_buffer + offset) = pixelColor;

			//Move to next pixel
			x = x + 1;
		}
		x = 0;
		y = y - 1;
	}
}

void SetSourceImage()
{
	// First byte was read, everything that follows starts the data
	short * ImageStoarge = (short *) SOURCE_IMAGE_STOARGE_MEM_LOC; // mock Pixel buffer to store source image
	int x = 0;	// x and y offset with top left as 0,0
	int y = 239;
	int offest = 0;
	int red, green, blue;
	unsigned short pixelColor = 0;

	/*
	 * Image will be sent with bottom left being first at 0,0 and a row at a time
	 */
	printf("Reading and saving image\n");
	// keep reading the buffer
	// Variables for the serial communication
		volatile int * SerialDataRegister = (int *) SERIAL_DATA_REGISTER;	// Data register of serial port
		int regValue = 0;
		int Shade = 0;
		int RVALID = 0;

	while(y >= 0) // loop until the picture is filled
	{
		while(x < 320) // loop until the row is filled
		{
			regValue = *(SerialDataRegister);
			RVALID = regValue & 0x00008000;
			Shade = regValue & 0x000000ff;
			if (RVALID) // this byte is good, use it
			{
				*(ImageStoarge + offset) = Shade;
				x = x + 1;
			}
		}
		x = 0;
		y = y -1 1;
	}
	updateVGA();
}

void setOverlayImage()
{
	// First byte was read, everything that follows starts the data
	short * OverlayStoarge = (short *) OVERLAY_IMAGE_STOARGE_MEM_LOC; // mock Pixel buffer to store overlay image
	int x = 0;	// x and y offset with top left as 0,0
	int y = 239;
	int offest = 0;
	int red, green, blue;
	unsigned short pixelColor = 0;

	/*
	 * Image will be sent with bottom left being first at 0,0 and a row at a time
	 */
	printf("Reading and saving overlay image\n");
	// keep reading the buffer
	// Variables for the serial communication
		volatile int * SerialDataRegister = (int *) SERIAL_DATA_REGISTER;	// Data register of serial port
		int regValue = 0;
		int Shade = 0;
		int RVALID = 0;

	while(y >= 0) // loop until the picture is filled
	{
		while(x < 320) // loop until the row is filled
		{
			regValue = *(SerialDataRegister);
			RVALID = regValue & 0x00008000;
			Shade = regValue & 0x000000ff;
			if (RVALID) // this byte is good, use it
			{
				*(OverlayStoarge + offset) = Shade;
				x = x + 1;
			}
		}
		x = 0;
		y = y - 1;
	}
	updateVGA();
}

void adjustBrightness()
{
	// will be getting a signed number -127 to 127
	volatile int * SerialDataRegister = (int *) SERIAL_DATA_REGISTER; // Data register of serial port
	int regValue = 0;
	int RVALID = 0;
	signed char value = 0;
	bool received = false;

	regValue = *(SerialDataRegister);
	while (!received)
	{
		regValue = *(SerialDataRegister);
		RVALID = regValue & 0x00008000;
		value = regValue & 0x000000ff;
		if (RVALID) // this byte is good, use it
		{
			brightness = value;
		}
	}
	updateVGA();
}

void adjustBrightness()
{
	// will be unsigned 0 to 255, divide by 100 to get multiplier
	volatile int * SerialDataRegister = (int *) SERIAL_DATA_REGISTER; // Data register of serial port
	int regValue = 0;
	int RVALID = 0;
	int value = 0;
	bool received = false;

	regValue = *(SerialDataRegister);
	while (!received)
	{
		regValue = *(SerialDataRegister);
		RVALID = regValue & 0x00008000;
		value = regValue & 0x000000ff;
		if (RVALID) // this byte is good, use it
		{
			contrast = ((double)value) / 100.0;
		}
	}
	updateVGA();
}

int main()
{
	printf("Starting\n");
	// Variables for the serial communication
	volatile int * SerialDataRegister = (int *) SERIAL_DATA_REGISTER;	// Data register of serial port
	int regValue = 0;
	int receivedValue = 0;
	int RVALID = 0;

	// Set defaults for brightness and contrast
	brightness = 0;
	contrast = 1;


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
