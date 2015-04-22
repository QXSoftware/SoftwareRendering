#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

Vector2::Vector2(const Vector3& v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(const Vector4& v)
{
	x = v.x;
	y = v.y;
}
