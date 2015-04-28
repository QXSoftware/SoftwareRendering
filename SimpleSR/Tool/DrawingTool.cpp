#include <DrawingTool.h>
#include <Mathf.h>

COLORREF DrawingTool::GetSystemColor(const Color& col)
{
    int r = col.r * 255;
    int g = col.g * 255;
    int b = col.b * 255;
    r = Mathf::Clamp(r, 0, 255);
    g = Mathf::Clamp(g, 0, 255);
    b = Mathf::Clamp(b, 0, 255);
    return RGB(r, g, b);
}

Color DrawingTool::ConvertSystemColor(COLORREF col)
{
    auto r = static_cast<float>(GetRValue(col)) / 255.0f;
    auto g = static_cast<float>(GetGValue(col)) / 255.0f;
    auto b = static_cast<float>(GetBValue(col)) / 255.0f;
    return Color(r, g, b);
}

void DrawingTool::DrawPixel(ColorBuffer* cb, DepthBuffer* db, int x, int y, float z, Color col)
{
    auto depth = db->GetDepth(x, y);
    // ZTest LEqual
    if (z <= depth)
    {
        // ZWrite On
        db->SetDepth(x, y, z);
        auto dc = cb->GetDC();
        SetPixel(dc, x, y, GetSystemColor(col));
    }
}

void DrawingTool::DrawPixel(ColorBuffer* cb, DepthBuffer* db, const Vector3& v, Color col)
{
    DrawPixel(cb, db, Mathf::RoundToInt(v.x), Mathf::RoundToInt(v.y), v.z, col);
}

void DrawingTool::DrawLine(ColorBuffer* cb, DepthBuffer* db, int x0, int y0, float z0, int x1, int y1, float z1, Color col)
{
    int dx = x1 - x0, dy = y1 - y0, steps;
    float xIncrement, yIncrement, x = (float)x0, y = (float)y0;
    if (Mathf::Abs(dx) > Mathf::Abs(dy))
    {
        steps = Mathf::Abs(dx);
    }
    else
    {
        steps = Mathf::Abs(dy);
    }
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    DrawPixel(cb, db, x0, y0, z0, col);
    for (auto k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        Vector2 a(x0, y0);
        Vector2 b(x1, y1);
        Vector3 c(x, y);
        auto t = Mathf::LerpFactor(a, b, c);
        c.z = Mathf::Lerp(z0, z1, t);
        DrawPixel(cb, db, c, col);
    }
}

void DrawingTool::DrawLine(ColorBuffer* cb, DepthBuffer* db, const Vector3&v0, const Vector3&v1, Color col)
{
    DrawLine(cb, db,
        Mathf::RoundToInt(v0.x), Mathf::RoundToInt(v0.y), v0.z,
        Mathf::RoundToInt(v1.x), Mathf::RoundToInt(v1.y), v1.z, col);
}
