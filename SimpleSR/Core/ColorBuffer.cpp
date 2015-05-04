#include <ColorBuffer.h>
#include <DrawingTool.h>

ColorBuffer::ColorBuffer(int w, int h)
    :m_Width(w), m_Height(h)
{
    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();
    m_OriginDC = ::GetDC(g_MainWindowHwnd);
    SetBkMode(m_OriginDC, TRANSPARENT);
    m_MemoryDC = CreateCompatibleDC(m_OriginDC);
    SetBkMode(m_MemoryDC, TRANSPARENT);

    m_MemoryBitmapData.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_MemoryBitmapData.bmiHeader.biWidth = m_Width;
    m_MemoryBitmapData.bmiHeader.biHeight = m_Height;
    m_MemoryBitmapData.bmiHeader.biPlanes = 1;
    m_MemoryBitmapData.bmiHeader.biBitCount = 32;
    m_MemoryBitmapData.bmiHeader.biCompression = BI_RGB;

    m_MemoryBitmap = CreateDIBSection(m_MemoryDC, &m_MemoryBitmapData, DIB_RGB_COLORS, (void**)(&m_MemoryBitmapDataPointer), NULL, 0);
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
    auto c = DrawingTool::GetSystemColor(col);
    auto encodedCol = RGB(GetBValue(c), GetGValue(c), GetRValue(c));
    m_MemoryBitmapDataPointer[y * m_Width + x] = encodedCol;
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
