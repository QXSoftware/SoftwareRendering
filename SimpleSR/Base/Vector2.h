#ifndef Vector2_h__
#define Vector2_h__

class Vector3;
class Vector4;

class Vector2
{
public:
    float x;
    float y;

    Vector2()
        :x(0), y(0){}
    Vector2(float x, float y)
        :x(x), y(y){}
    Vector2(const Vector3& v);
    Vector2(const Vector4& v);
public:
    static float Dot(const Vector2& lhs, const Vector2& rhs);
    Vector2 normalized();
public:
    static Vector2 one;
    static Vector2 zero;
};

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2&v, float scale);
Vector2 operator*(float scale, const Vector2&v);
Vector2 operator/(const Vector2&v, float scale);

#endif // Vector2_h__
