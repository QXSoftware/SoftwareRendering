#include <Triangle.h>
#include <DrawingTool.h>

void Triangle::SetVertices(Vertex* v0, Vertex* v1, Vertex* v2)
{
    m_V0 = v0;
    m_V1 = v1;
    m_V2 = v2;
}

void Triangle::SetMatrixes(Matrix4x4* obj2w, Matrix4x4* obj2wi, Matrix4x4* v, Matrix4x4* p, Matrix4x4* vp, Matrix4x4* mvp)
{
    m_ObjectToWorld = obj2w;
    m_ObjectToWorldInversed = obj2wi;
    m_ViewMatrix = v;
    m_ProjectionMatrix = p;
    m_ViewPortMatrix = vp;
    m_MVP = mvp;
}

void Triangle::SetBuffers(ColorBuffer* cb, DepthBuffer* db)
{
    m_ColorBuf = cb;
    m_DepthBuf = db;
}

void Triangle::Render()
{
    auto v0 = *m_MVP * m_V0->Pos;
    auto v1 = *m_MVP * m_V1->Pos;
    auto v2 = *m_MVP * m_V2->Pos;

    v0 = v0 / v0.w;
    v1 = v1 / v1.w;
    v2 = v2 / v2.w;

    v0 = *m_ViewPortMatrix * v0;
    v1 = *m_ViewPortMatrix * v1;
    v2 = *m_ViewPortMatrix * v2;

    auto dc = m_ColorBuf->GetDC();
    DrawingTool::DrawLine(dc, v0.x, v0.y, v1.x, v1.y, Color::red);
    DrawingTool::DrawLine(dc, v0.x, v0.y, v2.x, v2.y, Color::red);
    DrawingTool::DrawLine(dc, v2.x, v2.y, v1.x, v1.y, Color::red);
}
