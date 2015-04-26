#include <Transform.h>
#include <Mathf.h>

void Transform::RebuildMatrix()
{
    m_LocalToWorldMatrix =
        Matrix4x4::RotateByZ(m_Rotation.z * Mathf::Deg2Rad)*
        Matrix4x4::RotateByY(m_Rotation.y * Mathf::Deg2Rad)*
        Matrix4x4::RotateByX(m_Rotation.x * Mathf::Deg2Rad)*
        Matrix4x4::Translate(m_Position);
    m_WorldToLocalMatrix = m_LocalToWorldMatrix.Inversed();
}

void Transform::SetPosition(const Vector3& pos)
{
    m_Position.x = pos.x;
    m_Position.y = pos.y;
    m_Position.z = pos.z;
    RebuildMatrix();
}

void Transform::SetPosition(float x, float y, float z)
{
    m_Position.x = x;
    m_Position.y = y;
    m_Position.z = z;
    RebuildMatrix();
}

void Transform::SetRotation(const Vector3& rot)
{
    m_Rotation.x = rot.x;
    m_Rotation.y = rot.y;
    m_Rotation.z = rot.z;
    RebuildMatrix();
}

void Transform::SetRotation(float x, float y, float z)
{
    m_Rotation.x = x;
    m_Rotation.y = y;
    m_Rotation.z = z;
    RebuildMatrix();
}
