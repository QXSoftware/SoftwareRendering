#include "ColorBuffer.h"
#include "DrawingTool.h"

ColorBuffer::ColorBuffer(int w, int h)
    :m_Width(w), m_Height(h)
{
    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();
    m_OriginDC = ::GetDC(g_MainWindowHwnd);
    m_MemoryDC = CreateCompatibleDC(m_OriginDC);
    m_MemoryBitmap = CreateCompatibleBitmap(m_OriginDC, screenWidth, screenHeight);
    SelectObject(m_MemoryDC, m_MemoryBitmap);
}

ColorBuffer::~ColorBuffer()
{
    ReleaseDC(g_MainWindowHwnd, m_OriginDC);
    m_OriginDC = NULL;
    DeleteObject(m_MemoryDC);
    m_MemoryDC = NULL;
    DeleteObject(m_MemoryBitmap);
    m_MemoryBitmap = NULL;
}

Color ColorBuffer::GetColor(int x, int y)
{
    auto col = GetPixel(m_MemoryDC, x, y);
    return DrawingTool::ConvertSystemColor(col);
}

void ColorBuffer::SetColor(int x, int y, const Color& col)
{
    SetPixel(m_MemoryDC, x, y, RGB(255 * col.r, 255 * col.g, 255 * col.b));
}

void ColorBuffer::Clear(const Color& col)
{
    RECT rect = { 0, 0, m_Width, m_Height };
    HBRUSH brush = CreateSolidBrush(DrawingTool::GetSystemColor(col));
    FillRect(m_MemoryDC, &rect, brush);
    DeleteObject(brush);
}

void ColorBuffer::Flush()
{
    BitBlt(m_OriginDC, 0, 0, m_Width, m_Height, m_MemoryDC, 0, 0, SRCCOPY);
}
