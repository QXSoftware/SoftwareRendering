#ifndef DrawingTool_h__
#define DrawingTool_h__

#include "Color.h"
#include <windows.h>

class DrawingTool
{
    DrawingTool() = delete;
    ~DrawingTool() = delete;
public:
    static COLORREF GetSystemColor(const Color& col);
    static Color ConvertSystemColor(COLORREF col);
    static void DrawPixel(HDC dc, int x, int y, Color col);
    static void DrawLine(HDC dc, int x0, int y0, int x1, int y1, Color col);
};

#endif // DrawingTool_h__
