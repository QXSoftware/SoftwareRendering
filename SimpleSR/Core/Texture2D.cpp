#include <Texture2D.h>
#include <DrawingTool.h>

Texture2D::Texture2D()
    :m_Bmp(NULL), m_MemDC(NULL)
{}

Texture2D::~Texture2D()
{
    if (m_Bmp != NULL)
    {
        DeleteObject(m_Bmp);
        m_Bmp = NULL;
    }
    if (m_MemDC != NULL)
    {
        DeleteDC(m_MemDC);
        m_MemDC = NULL;
    }
}

Texture2D* Texture2D::Load(tstring file)
{
    auto tex = new Texture2D();
    HANDLE bmp = LoadImage(NULL, file.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (bmp == NULL)
    {
        delete tex;
        return nullptr;
    }
    tex->m_Bmp = bmp;
    HDC memDC = CreateCompatibleDC(NULL);
    if (SelectObject(memDC, tex->m_Bmp) == NULL)
    {
        DeleteDC(memDC);
        delete tex;
        return nullptr;
    }
    tex->m_MemDC = memDC;
    GetObject(tex->m_Bmp, sizeof(tex->m_Tex), &tex->m_Tex);
    return tex;
}

int Texture2D::GetWidth()
{
    return m_Tex.bmWidth;
}

int Texture2D::GetHeight()
{
    return m_Tex.bmHeight;
}

Color Texture2D::GetColor(int x, int y)
{
    return DrawingTool::ConvertSystemColor(GetPixel(m_MemDC, x, y));
}

Color Texture2D::GetColor(const Vector2& uv)
{
    int x = uv.x * m_Tex.bmWidth;
    int y = (1 - uv.y) * m_Tex.bmHeight;
    return GetColor(x, y);
}
