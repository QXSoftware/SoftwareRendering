#ifndef Matrix_h__
#define Matrix_h__

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Matrix4x4
{
public:
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
public:
	Matrix4x4& operator=(const Matrix4x4&) = default;
	Matrix4x4(const Matrix4x4&) = default;
	Matrix4x4() = default;
	~Matrix4x4() = default;
public:
	Vector3 MultiplyVector(const Vector3& v)
	{
		Vector3 x;
		return x;
	}
};

#endif // Matrix_h__
