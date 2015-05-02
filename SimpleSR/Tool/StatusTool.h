#ifndef __StatusTool_h__
#define __StatusTool_h__

#include <Screen.h>
#include <MacrosAndDefines.h>
#include <windows.h>
#include <ColorBuffer.h>

extern HWND g_MainWindowHwnd;

class StatusTool
{
    StatusTool(const StatusTool&) = delete;
    StatusTool& operator=(const StatusTool&) = delete;

    ColorBuffer* m_ColorBuffer;
    HFONT m_Font;
public:
    StatusTool();
    ~StatusTool() = default;
    void SetColorBuffer(ColorBuffer* cb);
public:
    void DrawDebug(int x, int y, tstring s);
    void DrawFPS();
};

#endif // __StatusTool_h__