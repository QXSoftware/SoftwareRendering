#ifndef Color_h__
#define Color_h__

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color()
        :r(1), g(1), b(1), a(1)
    {}
    Color(float r, float g, float b, float a)
        :r(r), g(g), b(b), a(a)
    {}
    Color(float r, float g, float b)
        :r(r), g(g), b(b), a(1)
    {}
    ~Color() = default;

    static Color red;
    static Color green;
    static Color blue;
    static Color pink;

    Color& operator+=(const Color& c);
    Color& operator-=(const Color& c);
    Color& operator*=(const Color& c);
    Color& operator*=(float f);
    Color& operator/=(float f);
};

Color operator+(const Color& lhs, const Color& rhs);
Color operator-(const Color& lhs, const Color& rhs);
Color operator*(const Color& c, float f);
Color operator*(float f, const Color& c);
Color operator/(const Color& c, float f);

#endif // Color_h__
