#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

Vector3::Vector3(const Vector2& v)
	:z(0)
{
	x = v.x;
	y = v.y;
}

Vector3::Vector3(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
	auto x = -lhs.y * rhs.z + lhs.z * rhs.y;
	auto y = -lhs.z * rhs.x + lhs.x * rhs.z;
	auto z = -lhs.x * rhs.y + lhs.y * rhs.x;
	Vector3 v(x, y, z);
	return v;
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
