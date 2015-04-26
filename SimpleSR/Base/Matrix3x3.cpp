#include <Matrix3x3.h>

Matrix3x3 Matrix3x3::identity(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1);

Vector3 operator*(const Vector3& v, const Matrix3x3& m)
{
    Vector3 ret;
    ret.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20;
    ret.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21;
    ret.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22;
    return ret;
}

Vector3 operator*(const Matrix3x3& m, const Vector3& v)
{
    Vector3 ret;
    ret.x = v.x * m.m00 + v.y * m.m01 + v.z * m.m02;
    ret.y = v.x * m.m10 + v.y * m.m11 + v.z * m.m12;
    ret.z = v.x * m.m20 + v.y * m.m21 + v.z * m.m22;
    return ret;
}

Matrix3x3 operator*(const Matrix3x3&lhs, const Matrix3x3& rhs)
{
    Matrix3x3 ret;
    ret.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20;
    ret.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21;
    ret.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22;
    ret.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20;
    ret.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21;
    ret.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22;
    ret.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20;
    ret.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21;
    ret.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22;
    return ret;
}

float Matrix3x3::Determinant()
{
    auto a = Vector3(m00, m01, m02);
    auto b = Vector3(m10, m11, m12);
    auto c = Vector3(m20, m21, m22);
    return Vector3::Dot(Vector3::Cross(a, b), c);
}

Matrix3x3 Matrix3x3::Inversed()
{
    auto tmp = 1.0f / Determinant();
    auto c00 = m11*m22 - m12*m21;
    auto c01 = m10*m22 - m12*m20;
    auto c02 = m10*m21 - m11*m20;
    auto c10 = m01*m22 - m02*m21;
    auto c11 = m00*m22 - m02*m20;
    auto c12 = m00*m21 - m01*m20;
    auto c20 = m01*m12 - m02*m11;
    auto c21 = m00*m12 - m02*m10;
    auto c22 = m00*m11 - m01*m10;
    return Matrix3x3(
        tmp*c00, -tmp*c10, tmp*c20,
        -tmp*c01, tmp*c11, -tmp*c21,
        tmp*c02, -tmp*c12, tmp*c22);
}

Matrix3x3 Matrix3x3::Transposed()
{
    return Matrix3x3(
        m00, m10, m20,
        m01, m11, m21,
        m02, m12, m22);
}
