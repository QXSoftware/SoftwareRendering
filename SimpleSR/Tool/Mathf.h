#ifndef Mathf_h__
#define Mathf_h__

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
		return 0;
	}

	// Returns the cosine of angle f in radians.
	static float Cos(float f)
	{
		return 0;
	}

	// Returns the tangent of angle f in radians.
	static float Tan(float f)
	{
		return 0;
	}

	// Clamps a value between a minimum float and maximum float value.
	static float Clamp(float value, float min, float max)
	{
		return 0;
	}

	// Clamps a value between a minimum int and maximum int value.
	static int Clamp(int value, int min, int max)
	{
		return 0;
	}

	// Clamps value between 0 and 1 and returns value.
	static float Clamp01(float value)
	{
		return 0;
	}

	// Returns the smallest integer greater to or equal to f.
	static float Ceil(float f)
	{
		return 0;
	}

	// Returns the smallest integer greater to or equal to f.
	static int CeilToInt(float f)
	{
		return 0;
	}

	// Returns f raised to power p.
	static float Pow(float f, float p)
	{
		return 0;
	}

	// Returns f rounded to the nearest integer.
	static float Round(float f)
	{
		return 0;
	}

	// Returns f rounded to the nearest integer.
	static int RoundToInt(float f)
	{
		return 0;
	}

	// Returns square root of f.
	static float Sqrt(float f)
	{
		return 0;
	}
	
	// Interpolates between a and b by t. t is clamped between 0 and 1.
	static float Lerp(float from, float to, float t)
	{
		return 0;
	}

	// Returns the largest integer smaller to or equal to f.
	static float Floor(float f)
	{
		return 0;
	}
};

#endif // Mathf_h__
