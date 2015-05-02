#ifndef Camera_h__
#define Camera_h__

#include <Transform.h>
#include <Matrix4x4.h>
#include <Mesh.h>
#include <DirectionalLight.h>
#include <Color.h>
#include <ColorBuffer.h>
#include <DepthBuffer.h>

class Camera
{
    friend class SREngine;

    Matrix4x4 m_ProjectionMatrix;
    Matrix4x4 m_CameraToWorldMatrix;
    Matrix4x4 m_WorldToCameraMatrix;
    Matrix4x4 m_ViewPortMatrix;
    float m_FarClipPlane;
    float m_NearClipPlane;
    float m_FieldOfView;
    float m_Aspect;
    Color m_BackgroundColor;

    ColorBuffer* m_ColorBuffer;
    DepthBuffer* m_DepthBuffer;

    DirectionalLight m_DirectionalLight;
    Color m_AmbientColor;

    void UpdateMatrix();
public:
    Camera();
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
    void Render(Mesh* mesh);
};

#endif // Camera_h__
