#ifndef Mathf_h__
#define Mathf_h__

#include <math.h>
#include <Color.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <Vertex.h>

class Mathf
{
public:
    static const float Deg2Rad;
    static const float Rad2Deg;
    static const float Epsilon;
    static const float PI;
public:
    // Returns the absolute value of x.
    static inline int Abs(int x)
    {
        return abs(x);
    }

    // Returns the absolute value of x.
    static inline float Abs(float x)
    {
        return abs(x);
    }

    // Returns the sine of angle f in radians.
    static inline float Sin(float f)
    {
        return sin(f);
    }

    // Returns the cosine of angle f in radians.
    static inline float Cos(float f)
    {
        return cos(f);
    }

    // Returns the tangent of angle f in radians.
    static inline float Tan(float f)
    {
        return tan(f);
    }

    static inline float Cot(float f)
    {
        return 1.0f / tan(f);
    }

    // Clamps a value between a minimum float and maximum float value.
    static inline float Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    // Clamps a value between a minimum int and maximum int value.
    static inline int Clamp(int value, int min, int max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    // Clamps value between 0 and 1 and returns value.
    static inline float Clamp01(float value)
    {
        if (value < 0)
            return 0;
        if (value > 1.0f)
            return 1.0f;
        return value;
    }

    // Returns the smallest integer greater to or equal to f.
    static inline float Ceil(float f)
    {
        return ceil(f);
    }

    // Returns the smallest integer greater to or equal to f.
    static inline int CeilToInt(float f)
    {
        return (int)ceil(f);
    }

    // Returns the largest integer smaller to or equal to f.
    static inline float Floor(float f)
    {
        return floor(f);
    }

    // Returns the largest integer smaller to or equal to f.
    static inline int FloorToInt(float f)
    {
        return (int)f;
    }

    // Returns f rounded to the nearest integer.
    static inline float Round(float f)
    {
        return round(f);
    }

    // Returns f rounded to the nearest integer.
    static inline int RoundToInt(float f)
    {
        return (int)round(f);
    }

    // Returns f raised to power p.
    static inline float Pow(float f, float p)
    {
        return pow(f, p);
    }

    // Returns square root of f.
    static inline float Sqrt(float f)
    {
        return sqrt(f);
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static inline float Lerp(float a, float b, float t)
    {
        return a * (1 - t) + b * t;
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static inline Color Lerp(const Color& a, const Color& b, float t)
    {
        return Color(
            Lerp(a.r, b.r, t),
            Lerp(a.g, b.g, t),
            Lerp(a.b, b.b, t),
            Lerp(a.a, b.a, t));
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static inline Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
    {
        return Vector2(
            Lerp(a.x, b.x, t),
            Lerp(a.y, b.y, t));
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
    {
        return Vector3(
            Lerp(a.x, b.x, t),
            Lerp(a.y, b.y, t),
            Lerp(a.z, b.z, t));
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static inline Vector4 Lerp(const Vector4& a, const Vector4& b, float t)
    {
        return Vector4(
            Lerp(a.x, b.x, t),
            Lerp(a.y, b.y, t),
            Lerp(a.z, b.z, t),
            Lerp(a.w, b.w, t));
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static Vertex Lerp(const Vertex& a, const Vertex& b, float t)
    {
        Vertex v;
        v.Pos = Mathf::Lerp(a.Pos, b.Pos, t);
        v.UV = Mathf::Lerp(a.UV, b.UV, t);
        v.DiffCol = Mathf::Lerp(a.DiffCol, b.DiffCol, t);
        v.W = Mathf::Lerp(a.W, b.W, t);
        v.Code = Encode(v.Pos);
        return v;
    }

    static RegionCode Encode(Vector4& v)
    {
        RegionCode ret = 0;
        if (v.w > 0)
        {
            if (v.w + v.x < 0)
                ret |= CVV_LEFT;
            if (v.w - v.x < 0)
                ret |= CVV_RIGHT;
            if (v.w + v.y < 0)
                ret |= CVV_BOTTOM;
            if (v.w - v.y < 0)
                ret |= CVV_TOP;
            if (v.w + v.z < 0)
                ret |= CVV_NEAR;
            if (v.w - v.z < 0)
                ret |= CVV_FAR;
        }
        else
        {
            if (v.w + v.x > 0)
                ret |= CVV_LEFT;
            if (v.w - v.x > 0)
                ret |= CVV_RIGHT;
            if (v.w + v.y > 0)
                ret |= CVV_BOTTOM;
            if (v.w - v.y > 0)
                ret |= CVV_TOP;
            if (v.w + v.z > 0)
                ret |= CVV_NEAR;
            if (v.w - v.z > 0)
                ret |= CVV_FAR;
        }
        return ret;
    }

    // Get the interpolation of t between a and b.
    static inline float LerpFactor(const Vector2& a, const Vector2& b, const Vector2& t)
    {
        auto dx = Abs(a.x - b.x);
        auto dy = Abs(a.y - b.y);
        if (dx > dy)
        {
            if (dx != 0)
                return Abs(t.x - a.x) / dx;
        }
        else
        {
            if (dy != 0)
                return Abs(t.y - a.y) / dy;
        }
        return 0;
    }

    // Get the perspective correctted uv.
    // uvw = uv / z
    // w = 1 / z
    static inline Vector2 LerpUV(const Vector2& uvw0, const float& w0, const Vector2& uvw1, const float& w1, float t)
    {
        auto uv = Lerp(uvw0, uvw1, t) / Lerp(w0, w1, t);
        return Vector2(Clamp01(uv.x), Clamp01(uv.y));
    }

    // Returns largest of two or more values
    static inline float Max(float a, float b)
    {
        return a > b ? a : b;
    }

    // Returns whether the triangle is backface.
    static bool IsBackface(Vector3* v0, Vector3* v1, Vector3* v2, Matrix4x4* mvp, Matrix4x4* vp);
    static bool IsBackface(const Vector2& w0, const Vector2& w1, const Vector2& w2);
};

#endif // Mathf_h__
