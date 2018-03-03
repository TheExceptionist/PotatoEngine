#pragma once
#include <Windows.h>
#include "pt_types.h"

static const char* className;
static const char* windowName;


#ifndef WINDOW_DIMENSION
#define WINDOW_DIMENSION
	static const uint16 windowWidth = 640;
	static const uint16 windowHeight = 480;
#endif

static HWND mainWindow;

void RegisterWindow(HINSTANCE hInstance);
void InitWindow(HINSTANCE hInstance);
void SetBlackScreen(void);
void InitWin(HINSTANCE hInstance);
