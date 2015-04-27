#ifndef Texture2D_h__
#define Texture2D_h__

#include <windows.h>
#include <MacrosAndDefines.h>
#include <Color.h>
#include <Vector2.h>

class Texture2D
{
    HANDLE m_Bmp;
    HDC m_MemDC;
    BITMAP m_Tex;
    Texture2D();
public:
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    ~Texture2D();
public:
    static Texture2D* Load(tstring file);
    int GetWidth();
    int GetHeight();
    Color GetColor(int x, int y);
    Color GetColor(const Vector2& uv);
};

#endif // Texture2D_h__
