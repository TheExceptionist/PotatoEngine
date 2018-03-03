#pragma once
#include "win.h"

#define PIXEL_BITS 32
#define PLANES 1
#define PIXEL_BYTES PIXEL_BITS / 8

static int BUFFER_WIDTH = 640;
static int BUFFER_HEIGHT = 480;

static HWND mainVidWindow;

void VID_Init(HWND window);
void VID_Update(float timestep);
void VID_Shutdown(void);
