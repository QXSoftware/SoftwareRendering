#include <Texture2D.h>
#include <DrawingTool.h>

Texture2D::Texture2D()
    :m_MemoryBitmap(0), m_MemoryBitmapDataPointer(0), m_Width(0), m_Height(0)
{}

Texture2D::~Texture2D()
{
    if (m_MemoryBitmap != NULL)
    {
        DeleteObject(m_MemoryBitmap);
        m_MemoryBitmap = NULL;
    }
    m_MemoryBitmapDataPointer = NULL;
}

Texture2D* Texture2D::Load(tstring file)
{
    HANDLE bmp = LoadImage(NULL, file.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (bmp == NULL)
    {
        return nullptr;
    }
    HDC tmpDc = CreateCompatibleDC(NULL);
    if (SelectObject(tmpDc, bmp) == NULL)
    {
        DeleteDC(tmpDc);
        return nullptr;
    }
    BITMAP bitmap;
    GetObject(bmp, sizeof(bitmap), &bitmap);

    auto tex = new Texture2D();

    tex->m_Width = bitmap.bmWidth;
    tex->m_Height = bitmap.bmHeight;

    tex->m_MemoryBitmapData.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    tex->m_MemoryBitmapData.bmiHeader.biWidth = tex->m_Width;
    tex->m_MemoryBitmapData.bmiHeader.biHeight = tex->m_Height;
    tex->m_MemoryBitmapData.bmiHeader.biPlanes = 1;
    tex->m_MemoryBitmapData.bmiHeader.biBitCount = 32;
    tex->m_MemoryBitmapData.bmiHeader.biSizeImage = tex->m_Width * tex->m_Height * 4;
    tex->m_MemoryBitmapData.bmiHeader.biCompression = BI_RGB;

    auto tmpDc2 = CreateCompatibleDC(NULL);
    tex->m_MemoryBitmap = CreateDIBSection(tmpDc2, &tex->m_MemoryBitmapData, DIB_RGB_COLORS, (void**)(&tex->m_MemoryBitmapDataPointer), NULL, 0);
    SelectObject(tmpDc2, tex->m_MemoryBitmap);
    BitBlt(tmpDc2, 0, 0, tex->m_Width, tex->m_Height, tmpDc, 0, 0, SRCCOPY);

    DeleteDC(tmpDc);
    DeleteObject(bmp);
    DeleteDC(tmpDc2);

    return tex;
}

Color Texture2D::GetColor(int x, int y)
{
    if (x >= m_Width)
        x = m_Width - 1;
    if (y >= m_Height)
        y = m_Height - 1;
    auto p = m_MemoryBitmapDataPointer;
    auto b = p[y * m_Width * 4 + x * 4];
    auto g = p[y * m_Width * 4 + x * 4 + 1];
    auto r = p[y * m_Width * 4 + x * 4 + 2];
    return Color(r, g, b) / 255;
}

Color Texture2D::GetColor(const Vector2& uv)
{
    int x = uv.x * m_Width;
    int y = uv.y * m_Height;
    return GetColor(x, y);
}
