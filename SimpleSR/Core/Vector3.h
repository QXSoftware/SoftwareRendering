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
};

#endif // Vector3_h__
