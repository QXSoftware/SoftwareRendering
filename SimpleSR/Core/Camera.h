#ifndef Camera_h__
#define Camera_h__

#include "Transform.h"
#include "Matrix4x4.h"
#include "Mesh.h"

class Camera
{
    Matrix4x4 m_ProjectionMatrix;
    Matrix4x4 m_CameraToWorldMatrix;
    Matrix4x4 m_WorldToCameraMatrix;
    float m_FarClipPlane;
    float m_NearClipPlane;
    float m_Aspect;
    float m_FieldOfView;
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
    void SetAspect(float f);
    void SetFieldOfView(float f);
    void UpdateMatrix();
    void Render(const Mesh* mesh);
};

#endif // Camera_h__
