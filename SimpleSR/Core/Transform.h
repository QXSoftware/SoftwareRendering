#ifndef Transform_h__
#define Transform_h__

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Mathf.h"

class Transform
{
    Vector3 m_Position;
    Vector3 m_Rotation;
    Matrix4x4 m_LocalToWorldMatrix;
    Matrix4x4 m_WorldToLocalMatrix;
    void RebuildMatrix();
public:
    Transform()
        :m_Position(Vector3::zero), m_Rotation(Vector3::zero){}
    ~Transform() = default;
    Transform(const Transform&) = delete;
    Transform& operator=(const Transform&) = delete;
public:
    void SetPosition(const Vector3& pos);
    void SetPosition(float x, float y, float z);
    void SetRotation(const Vector3& rot);
    void SetRotation(float x, float y, float z);

    inline Vector3 GetPosition() const
    {
        return m_Position;
    }
    inline Vector3 GetRotation() const
    {
        return m_Rotation;
    }
    inline Matrix4x4 LocalToWorldMatrix() const
    {
        return m_LocalToWorldMatrix;
    }
    inline Matrix4x4 WorldToLocalMatrix() const
    {
        return m_WorldToLocalMatrix;
    }
};

#endif // Transform_h__
