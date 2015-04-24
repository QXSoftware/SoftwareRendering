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

void Camera::Render(const Mesh* mesh)
{
}

void Camera::UpdateMatrix()
{
    m_MVP = Matrix4x4::identity;
}
