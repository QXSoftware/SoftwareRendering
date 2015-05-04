#ifndef Texture2D_h__
#define Texture2D_h__

#include <windows.h>
#include <MacrosAndDefines.h>
#include <Color.h>
#include <Vector2.h>

class Texture2D
{
    BITMAPINFO m_MemoryBitmapData;
    HBITMAP m_MemoryBitmap;
    PBYTE m_MemoryBitmapDataPointer;

    int m_Width;
    int m_Height;

    Texture2D();
public:
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    ~Texture2D();
public:
    static Texture2D* Load(tstring file);
    inline int GetWidth() const
    {
        return m_Width;
    };
    inline int GetHeight() const
    {
        return m_Height;
    };
    Color GetColor(int x, int y);
    Color GetColor(const Vector2& uv);
};

#endif // Texture2D_h__
