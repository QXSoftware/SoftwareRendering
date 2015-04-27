#include <Triangle.h>
#include <DrawingTool.h>
#include <Mathf.h>

void Triangle::SetVertices(Vertex* v0, Vertex* v1, Vertex* v2)
{
    m_V0 = v0;
    m_V1 = v1;
    m_V2 = v2;
}

void Triangle::SetLight(DirectionalLight* l, Color a)
{
    m_DirectionalLight = l;
    m_AmbientColor = a;
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

void Triangle::ComputeVertexLighting(Vertex* v)
{
    v->PosWorld = (*m_ObjectToWorld) * v->Pos;
    v->NormalWorld = Vector3(v->Normal * (*m_ObjectToWorldInversed)).normalized();
    v->DiffCol = Mathf::Max(0, Vector3::Dot(v->NormalWorld, m_DirectionalLight->Direction))
        * m_DirectionalLight->Intensity * m_DirectionalLight->Col;
}

void Triangle::DrawWireFrame()
{
    auto v0 = *m_MVP * m_V0->Pos;
    auto v1 = *m_MVP * m_V1->Pos;
    auto v2 = *m_MVP * m_V2->Pos;

    auto vcvv0 = v0 / v0.w;
    auto vcvv1 = v1 / v1.w;
    auto vcvv2 = v2 / v2.w;

    v0 = *m_ViewPortMatrix * vcvv0;
    v1 = *m_ViewPortMatrix * vcvv1;
    v2 = *m_ViewPortMatrix * vcvv2;

    DrawingTool::DrawLine(m_ColorBuf, m_DepthBuf, Vector3(v0, vcvv0.z), Vector3(v1, vcvv1.z), Color::red);
    DrawingTool::DrawLine(m_ColorBuf, m_DepthBuf, Vector3(v0, vcvv0.z), Vector3(v2, vcvv2.z), Color::red);
    DrawingTool::DrawLine(m_ColorBuf, m_DepthBuf, Vector3(v2, vcvv2.z), Vector3(v1, vcvv1.z), Color::red);
}

void Triangle::SortVerticesByY()
{
    auto v0 = *m_MVP * m_V0->Pos;
    auto v1 = *m_MVP * m_V1->Pos;
    auto v2 = *m_MVP * m_V2->Pos;

    v0 = *m_ViewPortMatrix * (v0 / v0.w);
    v1 = *m_ViewPortMatrix * (v1 / v1.w);
    v2 = *m_ViewPortMatrix * (v2 / v2.w);

    if (v0.y > v1.y)
    {
        auto tmp = m_V1;
        m_V1 = m_V0;
        m_V0 = tmp;
        auto tmp2 = v1;
        v1 = v0;
        v0 = tmp2;
    }
    if (v2.y > v1.y)
    {
        return;
    }
    if (v2.y <= v1.y && v2.y >= v0.y)
    {
        auto tmp = m_V1;
        m_V1 = m_V2;
        m_V2 = tmp;
        return;
    }
    if (v2.y < v0.y)
    {
        auto tmp = m_V0;
        m_V0 = m_V2;
        m_V2 = tmp;
        tmp = m_V2;
        m_V2 = m_V1;
        m_V1 = tmp;
    }
}

void Triangle::DrawGouraud()
{
    SortVerticesByY();
    auto v0 = *m_MVP * m_V0->Pos;
    auto v1 = *m_MVP * m_V1->Pos;
    auto v2 = *m_MVP * m_V2->Pos;

    auto vcvv0 = v0 / v0.w;
    auto vcvv1 = v1 / v1.w;
    auto vcvv2 = v2 / v2.w;

    v0 = *m_ViewPortMatrix * vcvv0;
    v1 = *m_ViewPortMatrix * vcvv1;
    v2 = *m_ViewPortMatrix * vcvv2;

    // 三角形三个点的 Lambert 光照值，uv 以及深度值
    // 这三个值将进行 Gouraud 差值
    auto lit0 = m_V0->DiffCol; auto uv0 = m_V0->UV0; auto depth0 = vcvv0.z;
    auto lit1 = m_V1->DiffCol; auto uv1 = m_V1->UV0; auto depth1 = vcvv1.z;
    auto lit2 = m_V2->DiffCol; auto uv2 = m_V2->UV0; auto depth2 = vcvv2.z;

    auto stepY01 = static_cast<int>(Mathf::Abs(v0.y - v1.y));
    auto stepY02 = static_cast<int>(Mathf::Abs(v0.y - v2.y));
    auto stepY12 = static_cast<int>(Mathf::Abs(v1.y - v2.y));
    auto stepX01 = static_cast<int>(Mathf::Abs(v0.x - v1.x));
    auto stepX02 = static_cast<int>(Mathf::Abs(v0.x - v2.x));
    auto stepX12 = static_cast<int>(Mathf::Abs(v1.x - v2.x));
    auto incX01 = stepY01 == 0 ? 0 : (v0.x - v1.x) / (float)stepY01;
    auto incX02 = stepY02 == 0 ? 0 : (v0.x - v2.x) / (float)stepY02;
    auto incX12 = stepY12 == 0 ? 0 : (v1.x - v2.x) / (float)stepY12;

    for (auto k = 0; k < stepY02; k++)
    {
        if (k < stepY01)
        {
            Vector3 n0(v0.x - incX01 * k, v0.y + k);
            float t0 = Mathf::LerpFactor(v0, v1, n0);
            n0.z = Mathf::Lerp(depth0, depth1, t0);
            Vector2 n0uv = Mathf::Lerp(uv0, uv1, t0);
            Vector3 n1(v0.x - incX02 * k, v0.y + k);
            float t1 = Mathf::LerpFactor(v0, v2, n1);
            n1.z = Mathf::Lerp(depth0, depth2, t1);
            Vector2 n1uv = Mathf::Lerp(uv0, uv2, t0);

            int lineWidth = Mathf::RoundToInt(n1.x - n0.x);
            for (int i = 0; i < Mathf::Abs(lineWidth); i++)
            {
                auto lineInc = lineWidth > 0 ? i : -i;
                Vector3 n3(n0.x + lineInc, n0.y);
                float t3 = Mathf::LerpFactor(n0, n1, n3);
                n3.z = Mathf::Lerp(n0.z, n1.z, t3);
                Vector2 n3uv = Mathf::Lerp(n0uv, n1uv, t3);
                Color col(Color::green);
                if (m_Texture != nullptr)
                    col = m_Texture->GetColor(n3uv);
                DrawingTool::DrawPixel(m_ColorBuf, m_DepthBuf, n3, col);
            }
        }
        else
        {
            Vector3 n0(v1.x - incX12 * (k - stepY01), v0.y + k);
            float t0 = Mathf::LerpFactor(v1, v2, n0);
            n0.z = Mathf::Lerp(depth1, depth2, t0);
            Vector2 n0uv = Mathf::Lerp(uv1, uv2, t0);
            Vector3 n1(v0.x - incX02 * k, v0.y + k);
            float t1 = Mathf::LerpFactor(v0, v2, n1);
            n1.z = Mathf::Lerp(depth0, depth2, t1);
            Vector2 n1uv = Mathf::Lerp(uv0, uv2, t1);

            int lineWidth = Mathf::RoundToInt(n1.x - n0.x);
            for (int i = 0; i < Mathf::Abs(lineWidth); i++)
            {
                auto lineInc = lineWidth > 0 ? i : -i;
                Vector3 n3(n0.x + lineInc, n0.y);
                float t3 = Mathf::LerpFactor(n0, n1, n3);
                n3.z = Mathf::Lerp(n0.z, n1.z, t3);
                Vector2 n3uv = Mathf::Lerp(n0uv, n1uv, t3);
                Color col(Color::green);
                if (m_Texture != nullptr)
                    col = m_Texture->GetColor(n3uv);
                DrawingTool::DrawPixel(m_ColorBuf, m_DepthBuf, n3, col);
            }
        }
    }
}

void Triangle::SetTexture(Texture2D* t)
{
    m_Texture = t;
}

void Triangle::Render()
{
    ComputeVertexLighting(m_V0);
    ComputeVertexLighting(m_V2);
    ComputeVertexLighting(m_V1);

    DrawGouraud();
    DrawWireFrame();
}
