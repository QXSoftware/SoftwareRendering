#ifndef DrawingTool_h__
#define DrawingTool_h__

#include "Color.h"
#include <windows.h>

extern HWND g_MainWindowHwnd;

class DrawingTool
{
    DrawingTool() = delete;
    ~DrawingTool() = delete;
public:
    static void DrawPixel(int x, int y, Color col)
    {
        auto hdc = GetDC(g_MainWindowHwnd);
        if (hdc)
        {
            SetPixel(hdc, x, y, RGB(255 * col.r, 255 * col.g, 255 * col.b));
        }
        ReleaseDC(g_MainWindowHwnd, hdc);
    }
};

#endif // DrawingTool_h__
