#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

Vector4::Vector4(const Vector2& v)
	:z(0), w(0)
{
	x = v.x;
	y = v.y;
}

Vector4::Vector4(const Vector3& v)
	:w(0)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

float Vector4::Dot(const Vector4& lhs, const Vector4& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
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
