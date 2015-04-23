#ifndef Vector4_h__
#define Vector4_h__

class Vector2;
class Vector3;

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4()
        :x(0), y(0), z(0), w(0){}
    Vector4(float x, float y, float z, float w)
        :x(x), y(y), z(z), w(w){}
    Vector4(float x, float y, float z)
        :x(x), y(y), z(z), w(0){}
    Vector4(float x, float y)
        :x(x), y(y), z(0), w(0){}
    Vector4(const Vector2& v)
        :x(v.x), y(v.y), z(0), w(0){}
    Vector4(const Vector3& v)
        :x(v.x), y(v.y), z(v.z), w(0){}
    Vector4(const Vector3& v, float w)
        :x(v.x), y(v.y), z(v.z), w(w){}
public:
    Vector4 normalized();
    static float Dot(const Vector4& lhs, const Vector4& rhs);
public:
    static Vector4 one;
    static Vector4 zero;
};

Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
Vector4 operator*(const Vector4&v, float scale);
Vector4 operator*(float scale, const Vector4&v);
Vector4 operator/(const Vector4&v, float scale);

#endif // Vector4_h__
