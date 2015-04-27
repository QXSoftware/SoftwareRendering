#ifndef Mathf_h__
#define Mathf_h__

#include <math.h>
#include <Color.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

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

    // Get the interpolation of t between a and b.
    static inline float LerpFactor(const Vector2& a, const Vector2& b, const Vector2& t)
    {
        auto dx = Abs(a.x - b.x);
        auto dy = Abs(a.y - b.y);
        if (dx > dy)
        {
            return Abs(t.x - a.x) / dx;
        }
        else
        {
            return Abs(t.y - a.y) / dy;
        }
    }

    // Returns largest of two or more values
    static inline float Max(float a, float b)
    {
        return a > b ? a : b;
    }
};

#endif // Mathf_h__
