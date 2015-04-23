#ifndef Transform_h__
#define Transform_h__

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Mathf.h"

class Transform
{
    Vector3 m_Position;
    Vector3 m_Rotation;
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
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
};

#endif // Transform_h__
