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
