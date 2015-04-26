#include <Vector4.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Mathf.h>

Vector4 Vector4::one(1, 1, 1, 1);
Vector4 Vector4::zero(0, 0, 0, 0);

Vector4::Vector4(const Vector2& v)
    :x(v.x), y(v.y), z(0), w(0){}

Vector4::Vector4(const Vector3& v)
    : x(v.x), y(v.y), z(v.z), w(0){}

Vector4::Vector4(const Vector3& v, float w)
    : x(v.x), y(v.y), z(v.z), w(w){}

float Vector4::Dot(const Vector4& lhs, const Vector4& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Vector4 Vector4::normalized()
{
    auto magnitude = Mathf::Sqrt(x*x + y*y + z*z + w*w);
    if (magnitude == 0)
        return Vector4(x, y, z, w);
    auto tmp = 1.0f / magnitude;
    return Vector4(x * tmp, y * tmp, z * tmp, w * tmp);
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
    Vector4 ret;
    ret.x = lhs.x + rhs.x;
    ret.y = lhs.y + rhs.y;
    ret.z = lhs.z + rhs.z;
    ret.w = lhs.w + rhs.w;
    return ret;
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
    Vector4 ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    ret.z = lhs.z - rhs.z;
    ret.w = lhs.w - rhs.w;
    return ret;
}

Vector4 operator*(const Vector4&v, float scale)
{
    Vector4 ret;
    ret.x = v.x * scale;
    ret.y = v.y * scale;
    ret.z = v.z * scale;
    ret.w = v.w * scale;
    return ret;
}

Vector4 operator*(float scale, const Vector4&v)
{
    Vector4 ret;
    ret.x = v.x * scale;
    ret.y = v.y * scale;
    ret.z = v.z * scale;
    ret.w = v.w * scale;
    return ret;
}

Vector4 operator/(const Vector4&v, float scale)
{
    Vector4 ret;
    ret.x = v.x / scale;
    ret.y = v.y / scale;
    ret.z = v.z / scale;
    ret.w = v.w / scale;
    return ret;
}
