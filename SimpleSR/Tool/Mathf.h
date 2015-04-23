#ifndef Mathf_h__
#define Mathf_h__

#include <math.h>

class Mathf
{
public:
    const float Deg2Rad = 0.0174533f;
    const float Rad2Deg = 57.2958f;
    const float Epsilon = 1.4013e-045f;
    const float PI = 3.14159f;
public:
    // Returns the sine of angle f in radians.
    static float Sin(float f)
    {
        return sin(f);
    }

    // Returns the cosine of angle f in radians.
    static float Cos(float f)
    {
        return cos(f);
    }

    // Returns the tangent of angle f in radians.
    static float Tan(float f)
    {
        return tan(f);
    }

    // Clamps a value between a minimum float and maximum float value.
    static float Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    // Clamps a value between a minimum int and maximum int value.
    static int Clamp(int value, int min, int max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    // Clamps value between 0 and 1 and returns value.
    static float Clamp01(float value)
    {
        if (value < 0)
            return 0;
        if (value > 1.0f)
            return 1.0f;
        return value;
    }

    // Returns the smallest integer greater to or equal to f.
    static float Ceil(float f)
    {
        return ceil(f);
    }

    // Returns the smallest integer greater to or equal to f.
    static int CeilToInt(float f)
    {
        return (int)ceil(f);
    }

    // Returns the largest integer smaller to or equal to f.
    static float Floor(float f)
    {
        return floor(f);
    }

    // Returns f raised to power p.
    static float Pow(float f, float p)
    {
        return pow(f, p);
    }

    // Returns square root of f.
    static float Sqrt(float f)
    {
        return sqrt(f);
    }

    // Interpolates between a and b by t. t is clamped between 0 and 1.
    static float Lerp(float from, float to, float t)
    {
        return (to - from) * t;
    }
};

#endif // Mathf_h__
