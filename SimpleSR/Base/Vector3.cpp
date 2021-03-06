#include <Vector3.h>
#include <Vector2.h>
#include <Vector4.h>
#include <Mathf.h>

Vector3 Vector3::one(1, 1, 1);
Vector3 Vector3::zero(0, 0, 0);
Vector3 Vector3::left(-1, 0, 0);
Vector3 Vector3::right(1, 0, 0);
Vector3 Vector3::up(0, 1, 0);
Vector3 Vector3::down(0, -1, 0);
Vector3 Vector3::forward(0, 0, 1);
Vector3 Vector3::backward(0, 0, -1);

Vector3::Vector3(const Vector2& v)
    :x(v.x), y(v.y), z(0){}

Vector3::Vector3(const Vector2& v, float z)
    : x(v.x), y(v.y), z(z){}

Vector3::Vector3(const Vector4& v)
    : x(v.x), y(v.y), z(v.z){}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
    auto x = lhs.y * rhs.z - lhs.z * rhs.y;
    auto y = lhs.z * rhs.x - lhs.x * rhs.z;
    auto z = lhs.x * rhs.y - lhs.y * rhs.x;
    return Vector3(x, y, z);
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::normalized()
{
    auto magnitude = Mathf::Sqrt(x*x + y*y + z*z);
    if (magnitude == 0)
        return Vector3(x, y, z);
    auto tmp = 1.0f / magnitude;
    return Vector3(x * tmp, y * tmp, z * tmp);
}

bool operator==(const Vector3&lhs, const Vector3& rhs)
{
    return lhs.x == rhs.x
        && lhs.y == rhs.y
        && lhs.z == rhs.z;
}

bool operator!=(const Vector3&lhs, const Vector3& rhs)
{
    return !(lhs == rhs);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 ret;
    ret.x = lhs.x + rhs.x;
    ret.y = lhs.y + rhs.y;
    ret.z = lhs.z + rhs.z;
    return ret;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    ret.z = lhs.z - rhs.z;
    return ret;
}

Vector3 operator*(const Vector3&v, float scale)
{
    Vector3 ret;
    ret.x = v.x * scale;
    ret.y = v.y * scale;
    ret.z = v.z * scale;
    return ret;
}

Vector3 operator*(float scale, const Vector3&v)
{
    Vector3 ret;
    ret.x = v.x * scale;
    ret.y = v.y * scale;
    ret.z = v.z * scale;
    return ret;
}

Vector3 operator/(const Vector3&v, float scale)
{
    Vector3 ret;
    ret.x = v.x / scale;
    ret.y = v.y / scale;
    ret.z = v.z / scale;
    return ret;
}
