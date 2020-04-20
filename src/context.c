#include "context.h"
#include "types.h"
#include "graphics.h"
#include "input.h"
#include <windows.h>
#include <stdio.h>

// Structs for handing events
// WM_KEYDOWN & WM_KEYUP
typedef struct
{
	// Repeat count for this key
	u32 repeat		: 16;
	// Hardware scancode of key
	u32 scancode	: 8;
	// Was extended (CTRL/ALT/etc)
	u32 extended	: 1;
	// Dont touch!
	u32 reserved	: 4;
	// Context code, always 0 for WM_KEYDOWN
	u32 context		: 1;
	// Previous key state (1 if key was down, 0 if it was up)
	u32 previous	: 1;
	// Always 0 
	u32 transition	: 1;
} Win_Key_Params;

Context context;

HWND wnd_hndl;
bool window_open = false;
HBITMAP bmp_hndl;

HDC wnd_dc;
HDC bmp_dc;

LARGE_INTEGER time_frequency;
LARGE_INTEGER time_last_tic;
f32 frame_delta = 0.f;
u32 tic_num = 0;

LRESULT CALLBACK wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_SIZE:
		{
			typedef struct
			{
				u16 width;
				u16 height;
			} Win_Size;

			Win_Size* size = (Win_Size*)&lParam;
			context.width = size->width;
			context.height = size->height;

			break;
		}

		case WM_KEYDOWN:
		{
			Win_Key_Params* key = (Win_Key_Params*)&lParam;
			printf("Key pressed: 0x%00x\n", key->scancode);

			if (key->scancode == KEY_ESCAPE)
			{
				context_close();
				return 0;
			}

			break;
		}

		case WM_DESTROY:
		{
			window_open = false;
			break;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void context_open(const char* title, u32 width, u32 height)
{
	// Register class
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	HINSTANCE instance = GetModuleHandle(NULL);

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.hInstance = instance;
	wc.lpszClassName = "MyClass";
	wc.lpfnWndProc = wnd_proc;

	RegisterClassEx(&wc);

	// Open windows!
	context.width = width;
	context.height = height;

	wnd_hndl = CreateWindow(
		wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, width, height,
		0, 0,
		instance,
		0
	);

	// Create the bitmap yo
	wnd_dc = GetDC(wnd_hndl);
	bmp_dc = CreateCompatibleDC(wnd_dc);
	bmp_hndl = CreateCompatibleBitmap(wnd_dc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(bmp_dc, bmp_hndl);

	window_open = true;

	// Init time
	QueryPerformanceFrequency(&time_frequency);
	QueryPerformanceCounter(&time_last_tic);
}

bool context_is_open()
{
	return window_open;
}

void context_close()
{
	if (!window_open)
		return;

	DestroyWindow(wnd_hndl);
	window_open = false;
}

void context_debug_pause()
{
	context_end_frame();
	Sleep(20);
}

u32 context_begin_frame()
{
	// Update delta time
	LARGE_INTEGER time_now;
	QueryPerformanceCounter(&time_now);

	u32 num_tics = (u32)((time_now.QuadPart - time_last_tic.QuadPart) / (time_frequency.QuadPart / TIC_RATE));
	time_last_tic.QuadPart += num_tics * (time_frequency.QuadPart / TIC_RATE);

	return num_tics;
}

void context_end_frame()
{
	// Dispatch all messages
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Set bitmap data
	BITMAPINFO info;
	memset(&info, 0, sizeof(info));

	info.bmiHeader.biSize = sizeof(info.bmiHeader);
	info.bmiHeader.biWidth = SCREEN_WIDTH;
	info.bmiHeader.biHeight = SCREEN_HEIGHT;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = SCREEN_CHANNELS * 8;

	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biSizeImage = 0;
	SetDIBits(wnd_dc, bmp_hndl, 0, SCREEN_HEIGHT, screen, &info, DIB_RGB_COLORS);

	// Blit to screen
	StretchBlt(wnd_dc, 0, 0, context.width, context.height, bmp_dc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SRCCOPY);
}