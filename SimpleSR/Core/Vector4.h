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

	Vector4() = default;
	Vector4(float x, float y, float z, float w)
		:x(x), y(y), z(z), w(w){}
	Vector4(float x, float y, float z)
		:x(x), y(y), z(z){}
	Vector4(float x, float y)
		:x(x), y(y){}
	Vector4(const Vector2& v);
	Vector4(const Vector3& v);
public:
	static float Dot(const Vector4& lhs, const Vector4& rhs);
};

Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
Vector4 operator*(const Vector4&v, float scale);
Vector4 operator*(float scale, const Vector4&v);
Vector4 operator/(const Vector4&v, float scale);

#endif // Vector4_h__
