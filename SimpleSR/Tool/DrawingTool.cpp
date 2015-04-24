#include "DrawingTool.h"

void DrawingTool::DrawPixel(int x, int y, Color col)
{
    auto hdc = GetDC(g_MainWindowHwnd);
    if (hdc)
    {
        SetPixel(hdc, x, y, RGB(255 * col.r, 255 * col.g, 255 * col.b));
    }
    ReleaseDC(g_MainWindowHwnd, hdc);
}
