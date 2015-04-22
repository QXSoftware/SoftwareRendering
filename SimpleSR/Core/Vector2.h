#ifndef Vector2_h__
#define Vector2_h__

class Vector3;
class Vector4;

class Vector2
{
public:
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y)
		:x(x), y(y){}
	Vector2(const Vector3& v);
	Vector2(const Vector4& v);
};

#endif // Vector2_h__
