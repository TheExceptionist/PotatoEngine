#include "pt_def.h"
#include "win.h"

static const char* className = "potatoe";
static const char* windowName = "Potatoe 32.exe";


//handle to the main window
static HWND mainWindow = NULL;


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg)
	{
	case WM_ACTIVATE:
		break;
	case WM_CREATE:
		break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		HOST_Shutdown();
		break;
	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
	//set the rest of the message to the defauilt operation, because I'm too lazy
	return result;
};

void InitWin(HINSTANCE hInstance)
{
	InitWindow(hInstance);
	VID_Init(mainWindow);
	SetBlackScreen();
}

//Required for the creation of a window in windows
void RegisterWindow(HINSTANCE hInstance)
{
	WNDCLASS wndClass = { 0 };
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndClass.lpszClassName = className;

	//Register class can fail, if it does it returns 0
	if (!RegisterClass(&wndClass))
	{
		printf("Could not register class!");
		getchar();
		exit(EXIT_FAILURE);
	}
}
//Initialize a window
void InitWindow(HINSTANCE hInstance)
{
	RegisterWindow(hInstance);
	//No need from extended windows functionality
	DWORD dwExStyle = 0;
	//window style is overlapped - has title and border and is visible
	DWORD dwStyle = WS_OVERLAPPED | WS_VISIBLE;

	//Create window
	mainWindow = CreateWindowEx(
		dwExStyle,
		className,
		windowName,
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(mainWindow, WS_VISIBLE);
}

void SetBlackScreen() 
{	//Device Context - contains drawing attribute to a window
	HDC DC = GetDC(mainWindow);
	//Fill the main area with a black color
	PatBlt(DC, 0, 0, windowWidth, windowHeight, BLACKNESS);
	//Release Context from the mainWindow- allow it's use for other applications i.e. good practice
	ReleaseDC(mainWindow, DC);
}

