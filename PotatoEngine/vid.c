#include "pt_def.h"
#include "vid.h"

BITMAPINFO DIB = { NULL };
int32* dblBuffer = NULL;

static void CreateDIB(void)
{
	//Number of fbytes required for the structure
	DIB.bmiHeader.biSize = sizeof(DIB);
	//Size of the bitmap
	DIB.bmiHeader.biWidth = BUFFER_WIDTH;
	DIB.bmiHeader.biHeight = BUFFER_HEIGHT;
	//always set to 1
	DIB.bmiHeader.biPlanes = PLANES;
	//Number of color bits per pixel
	DIB.bmiHeader.biBitCount = PIXEL_BITS;
}

static void Draw(int x, int y, int width, int height)
{
	int32* dest = dblBuffer;

	dest += (BUFFER_WIDTH * PIXEL_BYTES * y) + (x * PIXEL_BYTES);

	uint32* currentByte = (uint32*) dest;
	for (int y  = 0; y < BUFFER_HEIGHT; y++)
	{
		for (int x = 0; x < BUFFER_WIDTH; x++)
		{
			uint32 r = 0xFF;
			uint32 g = 0xFF;
			uint32 b = 0xFF;

			currentByte = (r << 16) | (g << 8) | b;
			currentByte++; 
		}
	}
}

void VID_Init(HWND window)
{
	mainVidWindow = window;

	//Allocate space for the double buffer
	dblBuffer = malloc((PIXEL_BYTES) * BUFFER_WIDTH * BUFFER_HEIGHT);

	CreateDIB();
}

void VID_Update(float timestep)
{
	Draw(0, 0, 50, 50);

	HDC DC = GetDC(mainVidWindow);

	//strectch the bitmap to the size of the screen
	StretchDIBits(
		DC,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		BUFFER_WIDTH,
		BUFFER_HEIGHT,
		dblBuffer,
		&DIB,
		DIB_RGB_COLORS,
		SRCCOPY
	);

	ReleaseDC(mainVidWindow, DC);
}

void VID_Shutdown(void)
{
	//free the dblBuffer
	free(dblBuffer);
	dblBuffer = NULL;
}
