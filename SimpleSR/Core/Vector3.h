#ifndef Vector3_h__
#define Vector3_h__

class Vector2;
class Vector4;

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3() = default;
    Vector3(float x, float y, float z)
        :x(x), y(y), z(z){}
    Vector3(float x, float y)
        :x(x), y(y){}

    Vector3(const Vector2& v);
    Vector3(const Vector4& v);
public:
    static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
    static float Dot(const Vector3& lhs, const Vector3& rhs);
public:
    static Vector3 one;
    static Vector3 zero;
};

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(const Vector3&v, float scale);
Vector3 operator*(float scale, const Vector3&v);
Vector3 operator/(const Vector3&v, float scale);

#endif // Vector3_h__
