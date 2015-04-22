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
