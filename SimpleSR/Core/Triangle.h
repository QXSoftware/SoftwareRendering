#ifndef __Triangle_h__
#define __Triangle_h__

#include <Vertex.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <ColorBuffer.h>
#include <DepthBuffer.h>
#include <Texture2D.h>

class Triangle
{
    friend class Mesh;

    Vertex* m_V0;
    Vertex* m_V1;
    Vertex* m_V2;

    Matrix4x4* m_ViewPortMatrix;

    ColorBuffer* m_ColorBuf;
    DepthBuffer* m_DepthBuf;
    Texture2D* m_Texture;
    Color m_AmbientColor;

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
        m_ViewPortMatrix(0), m_ColorBuf(0), m_DepthBuf(0), m_Texture(0)
    {}
    ~Triangle() = default;
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
public:
    bool IsBackface();
    void Render();
};

#endif // __Triangle_h__