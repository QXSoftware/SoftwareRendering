#include <DrawingTool.h>
#include <Mathf.h>

COLORREF DrawingTool::GetSystemColor(const Color& col)
{
    return RGB(col.r * 255, col.g * 255, col.b * 255);
}

Color DrawingTool::ConvertSystemColor(COLORREF col)
{
    auto r = static_cast<float>(GetRValue(col)) / 255.0f;
    auto g = static_cast<float>(GetGValue(col)) / 255.0f;
    auto b = static_cast<float>(GetBValue(col)) / 255.0f;
    return Color(r, g, b);
}

void DrawingTool::DrawPixel(ColorBuffer* buf, int x, int y, Color col)
{
    auto dc = buf->GetDC();
    SetPixel(dc, x, y, GetSystemColor(col));
}

void DrawingTool::DrawLine(ColorBuffer* buf, int x0, int y0, int x1, int y1, Color col)
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
    DrawPixel(buf, Mathf::RoundToInt(x), Mathf::RoundToInt(y), col);
    for (auto k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        DrawPixel(buf, Mathf::RoundToInt(x), Mathf::RoundToInt(y), col);
    }
}
