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
    m_AmbientColor = Color(158, 106, 11) / 255;
    m_DirectionalLight.Col = Color(38, 208, 40) / 255;
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

void Camera::UpdateMatrix()
{
    m_CameraToWorldMatrix = Transform->LocalToWorldMatrix();
    m_WorldToCameraMatrix = Transform->WorldToLocalMatrix();
    m_ProjectionMatrix = Matrix4x4::Perspective(m_FieldOfView, m_Aspect, m_NearClipPlane, m_FarClipPlane);
    auto scrWidth = Screen::current->GetScreenWidth();
    auto scrHeight = Screen::current->GetScreenHeight();
    m_ViewPortMatrix = Matrix4x4::ViewPortMatrix(scrWidth, scrHeight);
}

void Camera::Render(std::vector<Mesh*>& meshList)
{
    m_ColorBuffer->Clear(m_BackgroundColor);
    m_DepthBuffer->Clear(1);

    for (auto mesh : meshList)
    {
        mesh->SetLight(&m_DirectionalLight, m_AmbientColor);
        auto rot = mesh->Transform->GetRotation();
        if (mesh->GetName() == _T("Cube"))
        {
            mesh->Transform->SetRotation(rot.x + 12 * SRTime::DeltaTime, rot.y + 15 * SRTime::DeltaTime, rot.z + 9 * SRTime::DeltaTime);
        }
        else if (mesh->GetName() == _T("Cylinder"))
        {
            mesh->Transform->SetRotation(rot.x + 23 * SRTime::DeltaTime, rot.y + 18 * SRTime::DeltaTime, rot.z + 30 * SRTime::DeltaTime);
        }
        else if (mesh->GetName() == _T("Capsule"))
        {
            mesh->Transform->SetRotation(rot.x + 16 * SRTime::DeltaTime, rot.y + 3 * SRTime::DeltaTime, rot.z + 14 * SRTime::DeltaTime);
        }
        mesh->Render(m_ColorBuffer, m_DepthBuffer, m_ProjectionMatrix, m_WorldToCameraMatrix, m_ViewPortMatrix);
    }

    g_StatusTool.DrawFPS();
    m_ColorBuffer->Flush();
}
