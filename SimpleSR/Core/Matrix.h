#ifndef Matrix_h__
#define Matrix_h__

class Matrix4x4
{
	float m_Data[4][4];
public:
	Matrix4x4& operator=(const Matrix4x4&) = default;
	Matrix4x4(const Matrix4x4&) = default;
	Matrix4x4()
	{
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				m_Data[i][j] = 0;
			}
		}
	}
	~Matrix4x4() = default;
public:
	float* operator[](int index)
	{
		return m_Data[index];
	}
};

#endif // Matrix_h__
