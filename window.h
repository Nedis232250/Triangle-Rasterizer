#pragma once
#include <windows.h>
#include <cstdio>
#include "rasterizer.h"

struct window_essentials {
	HWND window;
	HDC device_context;
	RECT window_rect;
};

struct window_attributes {
	unsigned int width = 1920;
	unsigned int height = 1080;
	bool running = true;
	void* pixels = nullptr;
	unsigned int* rasterizer = nullptr;
};

window_essentials W32G_CREATE_WINDOW(const wchar_t* class_name, const wchar_t* window_name, LRESULT(*w_proc)(HWND, UINT, WPARAM, LPARAM),
									 unsigned int width, unsigned int height, unsigned int x, unsigned int y);

void W32G_resize_handler(window_essentials W32G_window, window_attributes& w_attribs, BITMAPINFO& bmi);

inline void W32G_WINDOW_CURSOR(LPCWSTR cursor) {
	SetCursor(LoadCursorW(0, cursor));
	ShowCursor(1);
}

inline void message_handler() {
	MSG msg = { 0 };

	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

class W32G_CPLUSPLUS_ALLOC_CONSOLE {
	W32G_CPLUSPLUS_ALLOC_CONSOLE(void) {
		AllocConsole();

		FILE* new_stdin;
		FILE* new_stdout;
		freopen_s(&new_stdin, "CONIN$", "r", stdin);
		freopen_s(&new_stdout, "CONOUT$", "w", stdout);
	}

	~W32G_CPLUSPLUS_ALLOC_CONSOLE() {
		FreeConsole();
	}
};
