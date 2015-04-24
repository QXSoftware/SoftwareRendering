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
    static void DrawPixel(int x, int y, Color col);
};

#endif // DrawingTool_h__
