#include "Camera.h"
#include "Mesh.h"

Camera::Camera()
    :m_FarClipPlane(100),
    m_NearClipPlane(0.3f),
    m_FieldOfView(60),
    Transform(new ::Transform())
{}

Camera::~Camera()
{
    delete Transform;
    Transform = nullptr;
}

void Camera::SetFarClipPlane(float f)
{
    m_FarClipPlane = f;
    UpdateMatrix();
}

void Camera::SetNearClipPlane(float f)
{
    m_NearClipPlane = f;
    UpdateMatrix();
}

void Camera::SetAspect(float f)
{
    m_Aspect = f;
    UpdateMatrix();
}

void Camera::SetFieldOfView(float f)
{
    m_FieldOfView = f;
    UpdateMatrix();
}

void Camera::UpdateMatrix()
{
}

void Camera::Render(const Mesh* mesh)
{
}
