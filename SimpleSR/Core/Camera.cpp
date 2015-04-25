#include "Camera.h"
#include "Mesh.h"
#include "Screen.h"

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

void Camera::SetFieldOfView(float f)
{
    m_FieldOfView = f;
    UpdateMatrix();
}

void Camera::UpdateMatrix()
{
    m_CameraToWorldMatrix = Transform->LocalToWorldMatrix();
    m_WorldToCameraMatrix = Transform->WorldToLocalMatrix();
    auto aspect = Screen::current->GetAspect();
    m_ProjectionMatrix = Matrix4x4::Perspective(m_FieldOfView, aspect, m_NearClipPlane, m_FarClipPlane);
    auto scrWidth = Screen::current->GetScreenWidth();
    auto scrHeight = Screen::current->GetScreenHeight();
    m_ViewPortMatrix = Matrix4x4(
        scrWidth / 2, 0, 0, scrWidth / 2,
        0, -scrHeight / 2, 0, scrHeight / 2,
        0, 0, 1, 0,
        0, 0, 0, 1);
}

void Camera::Render(Mesh* mesh)
{
    UpdateMatrix();
    mesh->Render(m_ProjectionMatrix, m_WorldToCameraMatrix, m_ViewPortMatrix);
}
