#include "DrawingTool.h"
#include "Mathf.h"

void DrawingTool::DrawPixel(int x, int y, Color col)
{
    auto hdc = GetDC(g_MainWindowHwnd);
    if (hdc)
    {
        SetPixel(hdc, x, y, RGB(255 * col.r, 255 * col.g, 255 * col.b));
    }
    ReleaseDC(g_MainWindowHwnd, hdc);
}

void DrawingTool::DrawLine(int x0, int y0, int x1, int y1, Color col)
{
    int dx = x1 - x0, dy = y1 - y0, steps;
    float xIncrement, yIncrement, x = (float)x0, y = (float)y0;
    if (Mathf::Abs(dx) > Mathf::Abs(dy))
    {
        steps = Mathf::Abs(dx);
    }
    else
    {
        steps = Mathf::Abs(dy);
    }
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    DrawPixel(Mathf::RoundToInt(x), Mathf::RoundToInt(y), col);
    for (auto k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        DrawPixel(Mathf::RoundToInt(x), Mathf::RoundToInt(y), col);
    }
}
