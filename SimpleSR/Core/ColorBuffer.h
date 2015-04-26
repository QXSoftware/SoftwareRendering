#ifndef __ColorBuffer_h__
#define __ColorBuffer_h__

#include <windows.h>
#include "Color.h"
#include "Screen.h"

extern HWND g_MainWindowHwnd;

class ColorBuffer
{
    int m_Width;
    int m_Height;

    HDC m_OriginDC;
    HDC m_MemoryDC;
    HBITMAP m_MemoryBitmap;
public:
    ColorBuffer(int w, int h);
    ~ColorBuffer();
    ColorBuffer(const ColorBuffer&) = delete;
    ColorBuffer& operator=(const ColorBuffer&) = delete;
public:
    inline HDC GetDC()
    {
        return m_MemoryDC;
    }
    Color GetColor(int x, int y);
    void SetColor(int x, int y, const Color& col);
    void Clear(const Color& col);
    void Flush();
};

#endif // __ColorBuffer_h__
