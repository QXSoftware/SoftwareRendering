#include <Color.h>

Color Color::red(1, 0, 0);
Color Color::green(0, 1, 0);
Color Color::blue(0, 0, 1);

Color& Color::operator*=(float f)
{
    r *= f;
    g *= f;
    b *= f;
    return *this;
}

Color& Color::operator/=(float f)
{
    if (f != 0)
    {
        auto temp = 1.0f / f;
        r *= temp;
        g *= temp;
        b *= temp;
    }
    return *this;
}

Color& Color::operator+=(const Color& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

Color& Color::operator-=(const Color& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    return *this;
}

Color operator+(const Color& lhs, const Color& rhs)
{
    return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}

Color operator-(const Color& lhs, const Color& rhs)
{
    return Color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
}

Color operator*(const Color& c, float f)
{
    return Color(c.r * f, c.g * f, c.b * f);
}

Color operator*(float f, const Color& c)
{
    return Color(c.r * f, c.g * f, c.b * f);
}

Color operator/(const Color& c, float f)
{
    Color ret;
    if (f != 0)
    {
        auto temp = 1.0f / f;
        ret.r = c.r * temp;
        ret.g = c.g * temp;
        ret.b = c.b * temp;
    }
    return ret;
}
