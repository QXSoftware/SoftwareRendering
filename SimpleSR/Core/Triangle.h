#ifndef __Triangle_h__
#define __Triangle_h__

#include <Vertex.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <ColorBuffer.h>
#include <DepthBuffer.h>
#include <DirectionalLight.h>

class Triangle
{
    Vertex* m_V0;
    Vertex* m_V1;
    Vertex* m_V2;

    Matrix4x4* m_ObjectToWorld;// 用于计算顶点的世界坐标
    Matrix4x4* m_ObjectToWorldInversed;// 用于计算法线的世界坐标
    Matrix4x4* m_ViewMatrix;
    Matrix4x4* m_ProjectionMatrix;
    Matrix4x4* m_ViewPortMatrix;
    Matrix4x4* m_MVP;

    DirectionalLight* m_DirectionalLight;
    Color m_AmbientColor;

    ColorBuffer* m_ColorBuf;
    DepthBuffer* m_DepthBuf;

    void ComputeVertexLighting(Vertex* v);
public:
    Triangle() = default;
    ~Triangle() = default;
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
public:
    void SetVertices(Vertex* v0, Vertex* v1, Vertex* v2);
    void SetLight(DirectionalLight* l, Color a);
    void SetMatrixes(Matrix4x4* obj2w, Matrix4x4* obj2wi, Matrix4x4* v, Matrix4x4* p, Matrix4x4* vp, Matrix4x4* mvp);
    void SetBuffers(ColorBuffer* cb, DepthBuffer* db);
    void Render();
};

#endif // __Triangle_h__