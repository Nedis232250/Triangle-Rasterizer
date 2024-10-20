#include "window.h"

window_essentials W32G_CREATE_WINDOW(const wchar_t* class_name, const wchar_t* window_name, LRESULT(*w_proc)(HWND, UINT, WPARAM, LPARAM), unsigned int width, unsigned int height, unsigned int x, unsigned int y) {
	WNDCLASS w_class = { 0 };

	w_class.lpszClassName = class_name;
	w_class.lpfnWndProc = w_proc;
	w_class.hInstance = GetModuleHandleW(0);

	RegisterClassW(&w_class);

	HWND hwnd = CreateWindowExW(0, w_class.lpszClassName, window_name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, width, height, 0, 0, GetModuleHandleW(0), 0);
	
	RECT rect;
	GetClientRect(hwnd, &rect);

	window_essentials w_essentials{};

	w_essentials.window = hwnd;
	w_essentials.device_context = GetDC(w_essentials.window);
	w_essentials.window_rect = rect;

	return w_essentials;
}

void W32G_resize_handler(window_essentials W32G_window, window_attributes& w_attribs, BITMAPINFO& bmi) {
    GetClientRect(W32G_window.window, &W32G_window.window_rect);
    w_attribs.width = W32G_window.window_rect.right - W32G_window.window_rect.left;
    w_attribs.height = W32G_window.window_rect.bottom - W32G_window.window_rect.top;

    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = w_attribs.width;
    bmi.bmiHeader.biHeight = w_attribs.height;

    if (w_attribs.pixels) {
        free(w_attribs.pixels);
    }

    w_attribs.pixels = w_attribs.pixels = malloc(static_cast<size_t>(w_attribs.width) * w_attribs.height * sizeof(unsigned int));
    w_attribs.rasterizer = (unsigned int*)w_attribs.pixels;
    W32G_SET_DIMENSIONS(w_attribs.width, w_attribs.height);
}
