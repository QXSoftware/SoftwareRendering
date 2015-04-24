#ifndef Mathf_h__
#define Mathf_h__

#include <math.h>

class Mathf
{
public:
    static const float Deg2Rad;
    static const float Rad2Deg;
    static const float Epsilon;
    static const float PI;
public:
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
    static inline float Lerp(float from, float to, float t)
    {
        return (to - from) * t;
    }
};

#endif // Mathf_h__
