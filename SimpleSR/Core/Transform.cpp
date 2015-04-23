#include "Transform.h"

void Transform::SetPosition(const Vector3& pos)
{
    m_Position.x = pos.x;
    m_Position.y = pos.y;
    m_Position.z = pos.z;
}

void Transform::SetPosition(float x, float y, float z)
{
    m_Position.x = x;
    m_Position.y = y;
    m_Position.z = z;
}

void Transform::SetRotation(const Vector3& rot)
{
    m_Rotation.x = rot.x;
    m_Rotation.y = rot.y;
    m_Rotation.z = rot.z;
}

void Transform::SetRotation(float x, float y, float z)
{
    m_Position.x = x;
    m_Position.y = y;
    m_Position.z = z;
}

Vector3 Transform::GetPosition() const
{
    return m_Position;
}

Vector3 Transform::GetRotation() const
{
    return m_Rotation;
}
