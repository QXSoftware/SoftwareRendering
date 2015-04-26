#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Mathf.h>

Vector2 Vector2::one(1, 1);
Vector2 Vector2::zero(0, 0);

Vector2::Vector2(const Vector3& v)
    :x(v.x), y(v.y){}

Vector2::Vector2(const Vector4& v)
    : x(v.x), y(v.y){}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::normalized()
{
    auto magnitude = Mathf::Sqrt(x*x + y*y);
    if (magnitude == 0)
        return Vector2(x, y);
    auto tmp = 1.0f / magnitude;
    return Vector2(x * tmp, y * tmp);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    Vector2 ret;
    ret.x = lhs.x + rhs.x;
    ret.y = lhs.y + rhs.y;
    return ret;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    Vector2 ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    return ret;
}

Vector2 operator*(float scale, const Vector2&v)
{
    Vector2 ret;
    ret.x = v.x * scale;
    ret.y = v.y * scale;
    return ret;
}

Vector2 operator*(const Vector2&v, float scale)
{
    Vector2 ret;
    ret.x = v.x * scale;
    ret.y = v.y * scale;
    return ret;
}

Vector2 operator/(const Vector2&v, float scale)
{
    Vector2 ret;
    ret.x = v.x / scale;
    ret.y = v.y / scale;
    return ret;
}
