#include <Mathf.h>
#include <Matrix3x3.h>

const float Mathf::Deg2Rad = 0.0174533f;
const float Mathf::Rad2Deg = 57.2958f;
const float Mathf::Epsilon = 1.4013e-045f;
const float Mathf::PI = 3.14159f;

bool Mathf::IsBackface(Vector3* v0, Vector3* v1, Vector3* v2, Matrix4x4* mvp, Matrix4x4* vp)
{
    auto w0 = (*mvp) * (Vector4(*v0, 1));
    auto w1 = (*mvp) * (Vector4(*v1, 1));
    auto w2 = (*mvp) * (Vector4(*v2, 1));
    w0 = (*vp) * (w0 / w0.w);
    w1 = (*vp) * (w1 / w1.w);
    w2 = (*vp) * (w2 / w2.w);

    return IsBackface(w0, w1, w2);
}

bool Mathf::IsBackface(const Vector2& w0, const Vector2& w1, const Vector2& w2)
{
    Matrix3x3 mat(
        w1.x - w0.x, w2.x - w0.x, w0.x,
        w1.y - w0.y, w2.y - w0.y, w0.y,
        0, 0, 1);

    return mat.Determinant() < 0;
}
