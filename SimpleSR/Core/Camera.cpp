#include <Camera.h>
#include <Mesh.h>
#include <Screen.h>
#include <functional>

Camera::Camera()
    :m_FarClipPlane(100),
    m_NearClipPlane(0.3f),
    m_FieldOfView(60),
    m_AmbientColor(0.1f, 0.1f, 0.3f)
{
    Transform = new ::Transform();
    Transform->SetCallback(std::bind(&Camera::UpdateMatrix, this));

    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();
    m_Aspect = (float)screenWidth / (float)screenHeight;

    m_DepthBuffer = new DepthBuffer(screenWidth, screenHeight);
    m_ColorBuffer = new ColorBuffer(screenWidth, screenHeight);

    m_DirectionalLight.Col = Color::red;
    m_DirectionalLight.Intensity = 0.5f;
    m_DirectionalLight.Direction = Vector3(30, 60, 20).normalized();
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
    m_ColorBuffer->Clear(m_AmbientColor);
    m_DepthBuffer->Clear(1);

    mesh->SetLight(&m_DirectionalLight, m_AmbientColor);
    mesh->Render(m_ColorBuffer, m_DepthBuffer, m_ProjectionMatrix, m_WorldToCameraMatrix, m_ViewPortMatrix);

    m_ColorBuffer->Flush();
}
