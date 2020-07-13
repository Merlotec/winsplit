// winsplit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>

#define DEF_SPLIT_COUNT 3
#define MAX_WINDOWS 10

// There seems to be an inexplicable gap between the windows even though the maths should add up to fill completely ???
// Therefore extra pixels needed to correcly space out the windows.
#define X_OFFSET 0
#define Y_OFFSET 0

#define HEIGHT_PADDING 0
#define WIDTH_PADDING 0

void GetVisibleWindows(HWND* windows, size_t max, size_t* count) {
	size_t windows_count = 0;

	for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
	{
		if (!IsWindowVisible(hwnd))
			continue;

		if (IsIconic(hwnd))
			continue;

		int length = GetWindowTextLengthA(hwnd);
		if (length == 0) 
			continue;

		char* title = malloc(length + 1);
		GetWindowTextA(hwnd, title, length + 1);

		if (
			strstr(title, "winsplit") != NULL ||
			strcmp(title, "winsplit.exe") == 0 ||
			strcmp(title, "Program Manager") == 0 ||
			strstr(title, "Command Prompt") != NULL ||
			strcmp(title, "Origin") == 0 ||
			strcmp(title, "Settings") == 0 ||
			strcmp(title, "Microsoft Store") == 0
			) {
			free(title);
			continue;
		}
		free(title);
		if (windows_count < max) {
			windows[windows_count] = hwnd;
			windows_count += 1;
			if (windows_count >= max) {
				break;
			}
		}
		else {
			break;
		}
	}
	if (count) {
		*count = windows_count;
	}
}

void GetDesktopResolution(int* horizontal, int* vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	*horizontal = desktop.right;
	*vertical = desktop.bottom;
}

BOOL GetTaskbarSize(LPSIZE size) {
	RECT rect;
	HWND taskBar = FindWindow(L"Shell_traywnd", NULL);
	if (taskBar && GetWindowRect(taskBar, &rect)) {
		size->cx = rect.right - rect.left;
		size->cy = rect.bottom - rect.top;
		return TRUE;
	}
	else {
		size->cx = 0;
		size->cy = 0;
		return FALSE;
	}
}

int main(int argc, char* argv[])
{
	int splitcount = 0;
	if (argc == 2) {
		splitcount = atoi(argv[1]);
	} 

	if (splitcount <= 0) {
		splitcount = DEF_SPLIT_COUNT;
	}

	SIZE taskbar_size;
	GetTaskbarSize(&taskbar_size);

	HWND windows[MAX_WINDOWS];
	size_t windows_count;

	GetVisibleWindows(windows, MAX_WINDOWS, &windows_count);

	if (windows_count < splitcount || splitcount <= 0) {
		splitcount = windows_count;
	}

	int dsk_w = 0, dsk_h = 0;
	GetDesktopResolution(&dsk_w, &dsk_h);
	int win_w = dsk_w / splitcount;
	int win_h = dsk_h - taskbar_size.cy;

	for (int i = 0; i < splitcount; i++) {
		SetWindowPos(windows[i], 0, win_w * i + X_OFFSET, Y_OFFSET, win_w + WIDTH_PADDING, win_h + HEIGHT_PADDING, SWP_SHOWWINDOW);
	}
	return 0;
}
