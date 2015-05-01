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
#include <Texture2D.h>
#include <MacrosAndDefines.h>

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
    Texture2D* m_Texture;

    RegionCode Encode(Vector4& v);

    void ComputeVertexLighting(Vertex* v);
    void SortVerticesByY();// 把三个顶点按照屏幕坐标从上到下排序，排序后 m_V0 为 y 最小的顶点，m_V2 为 y 最大的顶点
    void DrawWireFrame();
    // v1 和 v2 是在一条线上的，v0 是三角形的最顶或最低（y 轴）
    // 这个方法用于光栅化一个平底三角形或者“平顶”三角形
    void DrawSegment(
        const Vector2& v0, const Vector2& v1, const Vector2& v2,
        const float& w0, const float& w1, const float& w2,
        const Vector2& uvw0, const Vector2& uvw1, const Vector2& uvw2,
        const Color& lit0, const Color& lit1, const Color& lit2,
        const float& depth0, const float& depth1, const float& depth2);
    void DrawGouraud();
public:
    Triangle() :
        m_V0(0), m_V1(0), m_V2(0),
        m_ObjectToWorld(0), m_ObjectToWorldInversed(0), m_ViewMatrix(0),
        m_ProjectionMatrix(0), m_ViewPortMatrix(0), m_MVP(0),
        m_DirectionalLight(0), m_ColorBuf(0), m_DepthBuf(0), m_Texture(0)
    {}
    ~Triangle() = default;
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
public:
    void SetVertices(Vertex* v0, Vertex* v1, Vertex* v2);
    void SetLight(DirectionalLight* l, Color a);
    void SetMatrixes(Matrix4x4* obj2w, Matrix4x4* obj2wi, Matrix4x4* v, Matrix4x4* p, Matrix4x4* vp, Matrix4x4* mvp);
    void SetBuffers(ColorBuffer* cb, DepthBuffer* db);
    void SetTexture(Texture2D* t);
    void Render();
};

#endif // __Triangle_h__