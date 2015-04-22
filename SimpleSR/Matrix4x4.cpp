#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::identity(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);

Vector4 operator*(const Vector4& v, const Matrix4x4& m)
{
	Vector4 ret;
	ret.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30;
	ret.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31;
	ret.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32;
	ret.w = v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33;
	return ret;
}

Vector4 operator*(const Matrix4x4& m, const Vector4& v)
{
	Vector4 ret;
	ret.x = v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03;
	ret.y = v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13;
	ret.z = v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23;
	ret.w = v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33;
	return ret;
}

Matrix4x4 operator*(const Matrix4x4&lhs, const Matrix4x4& rhs)
{
	Matrix4x4 ret;
	ret.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30;
	ret.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31;
	ret.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32;
	ret.m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33;
	ret.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30;
	ret.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31;
	ret.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32;
	ret.m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33;
	ret.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30;
	ret.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31;
	ret.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32;
	ret.m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33;
	ret.m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30;
	ret.m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31;
	ret.m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32;
	ret.m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33;
	return ret;
}
