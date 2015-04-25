#ifndef Camera_h__
#define Camera_h__

#include "Transform.h"
#include "Matrix4x4.h"
#include "Mesh.h"
#include "DirectionalLight.h"
#include "Color.h"

class Camera
{
    Matrix4x4 m_ProjectionMatrix;
    Matrix4x4 m_CameraToWorldMatrix;
    Matrix4x4 m_WorldToCameraMatrix;
    Matrix4x4 m_ViewPortMatrix;
    float m_FarClipPlane;
    float m_NearClipPlane;
    float m_FieldOfView;
    float m_Aspect;//ͶӰƽ��߿��

    HDC m_ColorBufferDC;
    HBITMAP m_ColorBuffer;

    DirectionalLight m_DirectionalLight;
    Color m_AmbientColor;
public:
    Camera(HDC dc);
    ~Camera();
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
public:
    Transform* Transform;
public:
    void SetFarClipPlane(float f);
    void SetNearClipPlane(float f);
    void SetFieldOfView(float f);
    void SetAspect(float f);
    void UpdateMatrix();
    void Render(HWND hWnd, Mesh* mesh);
};

#endif // Camera_h__
