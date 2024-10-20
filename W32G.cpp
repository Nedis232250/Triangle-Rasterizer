#pragma once
#include <iostream>
#include <windows.h>

#include "rasterizer.h"
#include "window.h"

window_essentials W32G_window;
window_attributes w_attribs;
BITMAPINFO bmi;

LRESULT w_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            w_attribs.running = false;
            return 0;
        } break;
        case WM_SIZE: {
            W32G_resize_handler(W32G_window, w_attribs, bmi);
        } break;
    }

    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

int WinMain(HINSTANCE h_instance, HINSTANCE p_instance, LPSTR lpcmdln, int ncmd_show) {
    W32G_CPLUSPLUS_ALLOC_CONSOLE console(void);
    W32G_window = W32G_CREATE_WINDOW(L"class", L"W32G", w_proc, w_attribs.width, w_attribs.height, 0, 0);
    W32G_resize_handler(W32G_window, w_attribs, bmi);

    while (w_attribs.running) {
        message_handler();

        clear(w_attribs.rasterizer, { 1.0f, 1.0f, 1.0f });
        triangle(w_attribs.rasterizer, { 0.5, 0.5, { 0.0, 1.0, 0.0 }, 0.5 }, { 0.5, -0.5, { 1.0, 0.0, 0.0 }, 0.5 }, { -0.5, -0.5, { 0.0, 0.0, 1.0 }, 0.5 });
        
        StretchDIBits(W32G_window.device_context, 0, 0, w_attribs.width, w_attribs.height, 0, 0, w_attribs.width, w_attribs.height, w_attribs.rasterizer, &bmi, DIB_RGB_COLORS, SRCCOPY);
    }

    if (w_attribs.pixels) {
        free(w_attribs.pixels);
    }

    ReleaseDC(W32G_window.window, W32G_window.device_context);

    return 0;
}
