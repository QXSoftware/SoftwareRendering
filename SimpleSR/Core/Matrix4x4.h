#ifndef Matrix4x4_h__
#define Matrix4x4_h__

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
    Matrix4x4() :
        m00(0), m01(0), m02(0), m03(0),
        m10(0), m11(0), m12(0), m13(0),
        m20(0), m21(0), m22(0), m23(0),
        m30(0), m31(0), m32(0), m33(0)
    {}
    Matrix4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
        ) :
        m00(m00), m01(m01), m02(m02), m03(m03),
        m10(m10), m11(m11), m12(m12), m13(m13),
        m20(m20), m21(m21), m22(m22), m23(m23),
        m30(m30), m31(m31), m32(m32), m33(m33)
    {}
    ~Matrix4x4() = default;
public:
    float Determinant();//行列式
    Matrix4x4 Inversed();//逆矩阵
    Matrix4x4 Transposed();//转置矩阵

    static Matrix4x4 identity;
    static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);
    static Matrix4x4 Translate(const Vector3& v);
    static Matrix4x4 Scale(const Vector3& v);
    static Matrix4x4 RotateByX(float angle);
    static Matrix4x4 RotateByY(float angle);
    static Matrix4x4 RotateByZ(float angle);
};

Vector4 operator*(const Vector4& v, const Matrix4x4& m);
Vector4 operator*(const Matrix4x4& m, const Vector4& v);
Matrix4x4 operator*(const Matrix4x4&lhs, const Matrix4x4& rhs);

#endif // Matrix4x4_h__
