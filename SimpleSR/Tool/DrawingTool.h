#ifndef DrawingTool_h__
#define DrawingTool_h__

#include <Color.h>
#include <ColorBuffer.h>
#include <DepthBuffer.h>
#include <windows.h>
#include <Vector2.h>
#include <Vector3.h>

class DrawingTool
{
    DrawingTool() = delete;
    ~DrawingTool() = delete;
public:
    static COLORREF GetSystemColor(const Color& col);
    static Color ConvertSystemColor(COLORREF col);
    static void DrawPixel(ColorBuffer* cb, DepthBuffer* db, int x, int y, float z, Color col);
    static void DrawPixel(ColorBuffer* cb, DepthBuffer* db, const Vector3& v, Color col);
    static void DrawLine(ColorBuffer* cb, DepthBuffer* db, int x0, int y0, float z0, int x1, int y1, float z1, Color col);
    static void DrawLine(ColorBuffer* cb, DepthBuffer* db, const Vector3&v0, const Vector3&v1, Color col);
};

#endif // DrawingTool_h__
