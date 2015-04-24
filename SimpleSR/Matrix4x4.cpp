#include "Matrix4x4.h"
#include "Matrix3x3.h"

Matrix4x4 Matrix4x4::identity(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1);

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

float Matrix4x4::Determinant()
{
    Matrix3x3 mat0(
        m11, m12, m13,
        m21, m22, m23,
        m31, m32, m33);
    Matrix3x3 mat1(
        m10, m12, m13,
        m20, m22, m23,
        m30, m32, m33
        );
    Matrix3x3 mat2(
        m10, m11, m13,
        m20, m21, m23,
        m30, m31, m33);
    Matrix3x3 mat3(
        m10, m11, m12,
        m20, m21, m22,
        m30, m31, m32);
    return m00 * mat0.Determinant()
        - m01 * mat1.Determinant()
        + m02 * mat2.Determinant()
        - m03 * mat3.Determinant();
}

Matrix4x4 Matrix4x4::Inversed()
{
    auto tmp = 1.0f / Determinant();
    auto c00 = Matrix3x3(
        m11, m12, m13,
        m21, m22, m23,
        m31, m32, m33).Determinant();
    auto c01 = Matrix3x3(
        m10, m12, m13,
        m20, m22, m23,
        m30, m32, m33).Determinant();
    auto c02 = Matrix3x3(
        m10, m11, m13,
        m20, m21, m23,
        m30, m31, m33).Determinant();
    auto c03 = Matrix3x3(
        m10, m11, m12,
        m20, m21, m22,
        m30, m31, m32).Determinant();
    auto c10 = Matrix3x3(
        m01, m02, m03,
        m21, m22, m23,
        m31, m32, m33).Determinant();
    auto c11 = Matrix3x3(
        m00, m02, m03,
        m20, m22, m23,
        m30, m32, m33).Determinant();
    auto c12 = Matrix3x3(
        m00, m01, m03,
        m20, m21, m23,
        m30, m31, m33).Determinant();
    auto c13 = Matrix3x3(
        m00, m01, m02,
        m20, m21, m22,
        m30, m31, m32).Determinant();
    auto c20 = Matrix3x3(
        m01, m02, m03,
        m11, m12, m13,
        m31, m32, m33).Determinant();
    auto c21 = Matrix3x3(
        m00, m02, m03,
        m10, m12, m13,
        m30, m32, m33).Determinant();
    auto c22 = Matrix3x3(
        m00, m01, m03,
        m10, m11, m13,
        m30, m31, m33).Determinant();
    auto c23 = Matrix3x3(
        m00, m01, m02,
        m10, m11, m12,
        m30, m31, m32).Determinant();
    auto c30 = Matrix3x3(
        m01, m02, m03,
        m11, m12, m13,
        m21, m22, m23).Determinant();
    auto c31 = Matrix3x3(
        m00, m02, m03,
        m10, m12, m13,
        m20, m22, m23).Determinant();
    auto c32 = Matrix3x3(
        m00, m01, m03,
        m10, m11, m13,
        m20, m21, m23).Determinant();
    auto c33 = Matrix3x3(
        m00, m01, m02,
        m10, m11, m12,
        m20, m21, m22).Determinant();
    return Matrix4x4(
        tmp*c00, -tmp*c10, tmp*c20, -tmp*c30,
        -tmp*c01, tmp*c11, -tmp*c21, tmp*c31,
        tmp*c02, -tmp*c12, tmp*c22, -tmp*c32,
        -tmp*c03, tmp*c13, -tmp*c23, tmp*c33);
}

Matrix4x4 Matrix4x4::Transposed()
{
    return Matrix4x4(
        m00, m10, m20, m30,
        m01, m11, m21, m31,
        m02, m12, m22, m32,
        m03, m13, m23, m33);
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar)
{
    return identity;
}

Matrix4x4 Matrix4x4::Translate(const Vector3& v)
{
    return identity;
}

Matrix4x4 Matrix4x4::RotateByX(float angle)
{
    return identity;
}

Matrix4x4 Matrix4x4::RotateByY(float angle)
{
    return identity;
}

Matrix4x4 Matrix4x4::RotateByZ(float angle)
{
    return identity;
}
