//Sys.c 
//Handles the system calls and OS-related operations
//Author: Kenny Stepney

//--------------------------------------------------------------
//main.c
//Author: Kenny Stepney
//--------------------------------------------------------------
#include "pt_def.h"
#include "win.h"

static double GFreq;
static int64 GTimer;

//define class and window name to be used in the CreateWindowEx function
static int32 running = TRUE;

void InitSystems(HINSTANCE hInstance)
{
	InitWin(hInstance);
	InitHost();
	SYS_InitTimer();
}

void SYS_InitTimer(void)
{
	//Get the frequency of the system
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	//Get the frames per seconds
	GFreq = (double)freq.QuadPart;

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	GTimer = counter.QuadPart;
}

void SYS_Shutdown(void)
{
	running = FALSE;
}

//Standard windows entry point
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitSystems(hInstance);

	while(running)
	{
		LARGE_INTEGER timePassed;
		QueryPerformanceCounter(&timePassed);

		float timestep = (float)(timePassed.QuadPart - GTimer) / GFreq;

		Update(timestep);

		GTimer = timePassed.QuadPart;
	}

	return EXIT_SUCCESS;
}