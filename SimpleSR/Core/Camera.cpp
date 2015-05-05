#include <Camera.h>
#include <Mesh.h>
#include <Screen.h>
#include <functional>
#include <StatusTool.h>
#include <SRTime.h>

extern StatusTool g_StatusTool;

Camera::Camera()
    :m_FarClipPlane(100),
    m_NearClipPlane(0.3f),
    m_FieldOfView(60)
{
    Transform = new ::Transform();
    Transform->SetCallback(std::bind(&Camera::UpdateMatrix, this));

    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();
    m_Aspect = (float)screenWidth / (float)screenHeight;

    m_DepthBuffer = new DepthBuffer(screenWidth, screenHeight);
    m_ColorBuffer = new ColorBuffer(screenWidth, screenHeight);

    m_BackgroundColor = Color(49, 79, 126) / 255;
    m_AmbientColor = Color(155, 155, 155) / 255;
    m_DirectionalLight.Col = Color(186, 208, 80) / 255;
    m_DirectionalLight.Intensity = 0.9f;
    m_DirectionalLight.Direction = Vector3(-1, 1, 1).normalized();
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

void Camera::SetTranslationDelta(const Vector3& v)
{
    m_TranslationDelta += v;
}

void Camera::SetRotationDelta(const Vector3& v)
{
    m_RotationDelta += v;
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

void Camera::ResetTranslationDelta()
{
    m_TranslationDelta = Vector3::zero;
}

void Camera::ResetRotationDelta()
{
    m_RotationDelta = Vector3::zero;
}

void Camera::UpdateTransform()
{
    auto isDirty = false;
    if (m_TranslationDelta != Vector3::zero)
    {
        auto pos = Transform->GetPosition();
        Transform->SetPosition(pos + m_TranslationDelta * SRTime::DeltaTime);
        isDirty = true;
    }
    if (m_RotationDelta != Vector3::zero)
    {
        auto rot = Transform->GetRotation();
        Transform->SetRotation(rot + m_RotationDelta * SRTime::DeltaTime);
        isDirty = true;
    }
    if (isDirty)
    {
        m_CameraToWorldMatrix = Transform->LocalToWorldMatrix();
        m_WorldToCameraMatrix = Transform->WorldToLocalMatrix();
    }
}

void Camera::Render(std::vector<Mesh*>& meshList)
{
    m_ColorBuffer->Clear(m_BackgroundColor);
    m_DepthBuffer->Clear(1);

    UpdateTransform();

    for (auto mesh : meshList)
    {
        mesh->SetLight(&m_DirectionalLight, m_AmbientColor);
        auto rot = mesh->Transform->GetRotation();
        if (mesh->GetName() == _T("Tortoise"))
        {
            mesh->Transform->SetRotation(rot.x, rot.y + 15 * SRTime::DeltaTime, rot.z);
        }
        mesh->Render(m_ColorBuffer, m_DepthBuffer, m_ProjectionMatrix, m_WorldToCameraMatrix, m_ViewPortMatrix);
    }

    g_StatusTool.DrawFPS();
    g_StatusTool.DrawDebug(5, 30, _T("W、S、A、D 控制相机前后左右移动，Q 拉远镜头，E 拉近镜头，方向键控制相机旋转"));
    m_ColorBuffer->Flush();
}
