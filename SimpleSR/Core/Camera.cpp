#include "Camera.h"
#include "Mesh.h"
#include "Screen.h"

Camera::Camera(HDC dc)
    :m_FarClipPlane(100),
    m_NearClipPlane(0.3f),
    m_FieldOfView(60),
    m_Aspect(0.75),
    Transform(new ::Transform())
{
    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();
    m_ColorBufferDC = CreateCompatibleDC(dc);
    m_ColorBuffer = CreateCompatibleBitmap(dc, screenWidth, screenHeight);
    SelectObject(m_ColorBufferDC, m_ColorBuffer);
}

Camera::~Camera()
{
    DeleteObject(m_ColorBuffer);
    m_ColorBuffer = NULL;
    DeleteDC(m_ColorBufferDC);
    m_ColorBufferDC = NULL;
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
    m_ViewPortMatrix = Matrix4x4(
        scrWidth / 2, 0, 0, scrWidth / 2,
        0, -scrHeight / 2, 0, scrHeight / 2,
        0, 0, 1, 0,
        0, 0, 0, 1);
}

void Camera::Render(HWND hWnd, Mesh* mesh)
{
    UpdateMatrix();

    HDC hdc = GetDC(hWnd);
    auto screenWidth = Screen::current->GetScreenWidth();
    auto screenHeight = Screen::current->GetScreenHeight();

    RECT rect = { 0, 0, screenWidth, screenHeight };
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(m_ColorBufferDC, &rect, brush);

    mesh->Render(m_ColorBufferDC, m_ProjectionMatrix, m_WorldToCameraMatrix, m_ViewPortMatrix);

    BitBlt(hdc, 0, 0, screenWidth, screenHeight, m_ColorBufferDC, 0, 0, SRCCOPY);
}
