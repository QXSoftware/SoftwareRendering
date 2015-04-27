#ifndef DrawingTool_h__
#define DrawingTool_h__

#include <Color.h>
#include <ColorBuffer.h>
#include <windows.h>

class DrawingTool
{
    DrawingTool() = delete;
    ~DrawingTool() = delete;
public:
    static COLORREF GetSystemColor(const Color& col);
    static Color ConvertSystemColor(COLORREF col);
    static void DrawPixel(ColorBuffer* buf, int x, int y, Color col);
    static void DrawLine(ColorBuffer* buf, int x0, int y0, int x1, int y1, Color col);
};

#endif // DrawingTool_h__
