#ifndef Matrix3x3_h__
#define Matrix3x3_h__

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Matrix3x3
{
public:
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
public:
    Matrix3x3& operator=(const Matrix3x3&) = default;
    Matrix3x3(const Matrix3x3&) = default;
    Matrix3x3() :
        m00(0), m01(0), m02(0),
        m10(0), m11(0), m12(0),
        m20(0), m21(0), m22(0)
    {}
    Matrix3x3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22
        ) :
        m00(m00), m01(m01), m02(m02),
        m10(m10), m11(m11), m12(m12),
        m20(m20), m21(m21), m22(m22)
    {}
    ~Matrix3x3() = default;
public:
    float Determinant();//行列式
    Matrix3x3 Inversed();//逆矩阵
    Matrix3x3 Transposed();//转置矩阵

    static Matrix3x3 identity;
};

Vector3 operator*(const Vector4& v, const Matrix3x3& m);
Vector3 operator*(const Matrix3x3& m, const Vector3& v);
Matrix3x3 operator*(const Matrix3x3&lhs, const Matrix3x3& rhs);

#endif // Matrix3x3_h__
