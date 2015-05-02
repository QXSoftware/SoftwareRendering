#include <Triangle.h>
#include <DrawingTool.h>
#include <Mathf.h>
#include <vector>

void Triangle::DrawWireFrame()
{
    auto v0 = m_V0->Pos;
    auto v1 = m_V1->Pos;
    auto v2 = m_V2->Pos;

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
    auto v0 = m_V0->Pos;
    auto v1 = m_V1->Pos;
    auto v2 = m_V2->Pos;

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

void Triangle::DrawSegment(
    const Vector2& v0, const Vector2& v1, const Vector2& v2,
    const float& w0, const float& w1, const float& w2,
    const Vector2& uvw0, const Vector2& uvw1, const Vector2& uvw2,
    const Color& lit0, const Color& lit1, const Color& lit2,
    const float& depth0, const float& depth1, const float& depth2)
{
    bool v0yIsSmaller = v0.y < v2.y;
    int v0y = v0yIsSmaller ? Mathf::FloorToInt(v0.y) : Mathf::CeilToInt(v0.y);
    int v2y = v0yIsSmaller ? Mathf::CeilToInt(v2.y) : Mathf::FloorToInt(v2.y);
    for (int i = 0, height = Mathf::Abs(v0y - v2y); i <= height; i++)
    {
        float t0 = (float)i / (float)height;
        float dx01 = (v0.x - v1.x) / (float)height;
        float dx02 = (v0.x - v2.x) / (float)height;
        int deltaY = v0yIsSmaller ? 1 : -1;

        Vector3 n0(v0.x - dx01 * i, v0y + deltaY * i);
        n0.z = Mathf::Lerp(depth0, depth1, t0);
        auto n0uvw = Mathf::Lerp(uvw0, uvw1, t0);
        auto n0w = Mathf::Lerp(w0, w1, t0);
        Color n0lit = Mathf::Lerp(lit0, lit1, t0);

        Vector3 n1(v0.x - dx02 * i, v0y + deltaY * i);
        n1.z = Mathf::Lerp(depth0, depth2, t0);
        auto n1uvw = Mathf::Lerp(uvw0, uvw2, t0);
        auto n1w = Mathf::Lerp(w0, w2, t0);
        Color n1lit = Mathf::Lerp(lit0, lit2, t0);

        bool n0xIsSmaller = v1.x < v2.x;
        int n0x = n0xIsSmaller ? Mathf::FloorToInt(n0.x) : Mathf::CeilToInt(n0.x);
        int n1x = n0xIsSmaller ? Mathf::CeilToInt(n1.x) : Mathf::FloorToInt(n1.x);

        for (int j = 0, width = Mathf::Abs(n0x - n1x); j <= width; j++)
        {
            int deltaX = n0x < n1x ? 1 : -1;
            Vector3 n3(n0x + deltaX * j, n0.y);
            float t3 = Mathf::LerpFactor(n0, n1, n3);
            n3.z = Mathf::Lerp(n0.z, n1.z, t3);
            Vector2 n3uv = Mathf::LerpUV(n0uvw, n0w, n1uvw, n1w, t3);
            Color n3lit = Mathf::Lerp(n0lit, n1lit, t3);

            Color col(Color::pink);
            if (m_Texture != nullptr)
                col = m_Texture->GetColor(n3uv);
            col *= m_AmbientColor;
            col += n3lit;
            DrawingTool::DrawPixel(m_ColorBuf, m_DepthBuf, n3, col);
        }
    }
}

void Triangle::DrawGouraud()
{
    SortVerticesByY();

    auto v0 = m_V0->Pos;
    auto v1 = m_V1->Pos;
    auto v2 = m_V2->Pos;

    auto vcvv0 = v0 / v0.w;
    auto vcvv1 = v1 / v1.w;
    auto vcvv2 = v2 / v2.w;

    v0 = *m_ViewPortMatrix * vcvv0;
    v1 = *m_ViewPortMatrix * vcvv1;
    v2 = *m_ViewPortMatrix * vcvv2;

    auto w0 = m_V0->W;
    auto w1 = m_V1->W;
    auto w2 = m_V2->W;

    // 三角形三个点的 Lambert 光照值，uv 以及深度值
    // 这三个值将进行 Gouraud 差值
    auto lit0 = m_V0->DiffCol; auto uvw0 = m_V0->UV * w0; auto depth0 = vcvv0.z;
    auto lit1 = m_V1->DiffCol; auto uvw1 = m_V1->UV * w1; auto depth1 = vcvv1.z;
    auto lit2 = m_V2->DiffCol; auto uvw2 = m_V2->UV * w2; auto depth2 = vcvv2.z;

    if (v0.y == v1.y && v1.y == v2.y)
    {
        return;
    }
    else if (v0.x == v1.x && v1.x == v2.x)
    {
        return;
    }
    else if (v0.y == v1.y)
    {
        if (v0.x == v1.x)
            return;
        DrawSegment(
            v2, v0, v1,
            w2, w0, w1,
            uvw2, uvw0, uvw1,
            lit2, lit0, lit1,
            depth2, depth0, depth1);
    }
    else if (v1.y == v2.y)
    {
        if (v1.x == v2.x)
            return;
        DrawSegment(
            v0, v1, v2,
            w0, w1, w2,
            uvw0, uvw1, uvw2,
            lit0, lit1, lit2,
            depth0, depth1, depth2);
    }
    else
    {
        auto t3 = Mathf::Abs(v0.y - v1.y) / Mathf::Abs(v0.y - v2.y);
        auto v3 = Mathf::Lerp(v0, v2, t3);
        auto lit3 = Mathf::Lerp(lit0, lit2, t3);
        auto w3 = Mathf::Lerp(w0, w2, t3);
        auto uvw3 = Mathf::Lerp(uvw0, uvw2, t3);
        auto depth3 = Mathf::Lerp(depth0, depth2, t3);

        DrawSegment(
            v0, v1, v3,
            w0, w1, w3,
            uvw0, uvw1, uvw3,
            lit0, lit1, lit3,
            depth0, depth1, depth3);
        DrawSegment(
            v2, v1, v3,
            w2, w1, w3,
            uvw2, uvw1, uvw3,
            lit2, lit1, lit3,
            depth2, depth1, depth3);
    }
}

bool Triangle::IsBackface()
{
    auto v0 = m_V0->Pos;
    auto v1 = m_V1->Pos;
    auto v2 = m_V2->Pos;

    v0 = *m_ViewPortMatrix * v0 / v0.w;
    v1 = *m_ViewPortMatrix * v1 / v1.w;
    v2 = *m_ViewPortMatrix * v2 / v2.w;

    return Mathf::IsBackface(v0, v1, v2);
}

void Triangle::Render()
{
    if (IsBackface())
        return;
    DrawGouraud();
    //DrawWireFrame();
}
