#include "Camera.h"
#include "Mesh.h"
#include "Screen.h"

Camera::Camera()
    :m_FarClipPlane(100),
    m_NearClipPlane(0.3f),
    m_FieldOfView(60),
    Transform(new ::Transform()),
    m_AmbientColor(0.1f, 0.3f, 0.2f)
{
    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();
    m_Aspect = (float)screenWidth / (float)screenHeight;

    m_DepthBuffer = new DepthBuffer(screenWidth, screenHeight);
    m_ColorBuffer = new ColorBuffer(screenWidth, screenHeight);

    m_DirectionalLight.Col = Color::red;
    m_DirectionalLight.Intensity = 1.1f;
    m_DirectionalLight.Rotation = Vector3::zero;
}

Camera::~Camera()
{
    delete Transform;
    Transform = nullptr;
    delete m_DepthBuffer;
    m_DepthBuffer = nullptr;
    delete m_ColorBuffer;
    m_ColorBuffer = nullptr;
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

void Camera::SetAspect(float f)
{
    m_Aspect = f;
    UpdateMatrix();
}

void Camera::UpdateMatrix()
{
    m_CameraToWorldMatrix = Transform->LocalToWorldMatrix();
    m_WorldToCameraMatrix = Transform->WorldToLocalMatrix();
    m_ProjectionMatrix = Matrix4x4::Perspective(m_FieldOfView, m_Aspect, m_NearClipPlane, m_FarClipPlane);
    auto scrWidth = Screen::current->GetScreenWidth();
    auto scrHeight = Screen::current->GetScreenHeight();
    m_ViewPortMatrix = Matrix4x4::ViewPortMatrix(scrWidth, scrHeight);
}

void Camera::Render(Mesh* mesh)
{
    UpdateMatrix();
    m_ColorBuffer->Clear(m_AmbientColor);
    m_DepthBuffer->Clear(0);

    mesh->Render(m_ColorBuffer, m_DepthBuffer, m_ProjectionMatrix, m_WorldToCameraMatrix, m_ViewPortMatrix);

    m_ColorBuffer->Flush();
}
