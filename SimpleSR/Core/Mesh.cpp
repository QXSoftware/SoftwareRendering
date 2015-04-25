#include "Mesh.h"
#include "DrawingTool.h"

Mesh::Mesh()
    :Transform(new ::Transform())
{}

Mesh::~Mesh()
{
    Clear();
}

Color Mesh::ComputeColor(const DirectionalLight& d, const Color& a, const Vector3& n)
{
    return Color::green;
}

void Mesh::Render(HDC dc, const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp)
{
    auto mvp = p * v * Transform->LocalToWorldMatrix();
    Vector3* triangle[3];
    auto i = 0;
    for (auto iter = m_Triangles.begin(); iter != m_Triangles.end(); iter++)
    {
        triangle[i++] = m_Vertices[*iter];
        if (i > 2)
        {
            i = 0;
            ProcessTriangle(dc, triangle, mvp, vp);
        }
    }
}

void Mesh::ProcessTriangle(HDC dc, Vector3** triangle, const Matrix4x4& mvp, const Matrix4x4& vp)
{
    auto v0 = mvp * Vector4(*triangle[0], 1);
    auto v1 = mvp * Vector4(*triangle[1], 1);
    auto v2 = mvp * Vector4(*triangle[2], 1);

    v0 = v0 / v0.w;
    v1 = v1 / v1.w;
    v2 = v2 / v2.w;

    v0 = vp * v0;
    v1 = vp * v1;
    v2 = vp * v2;

    DrawingTool::DrawLine(dc, v0.x, v0.y, v1.x, v1.y, Color::red);
    DrawingTool::DrawLine(dc, v0.x, v0.y, v2.x, v2.y, Color::red);
    DrawingTool::DrawLine(dc, v2.x, v2.y, v1.x, v1.y, Color::red);
}

void Mesh::Clear()
{
    for (auto iter = m_Vertices.begin(); iter != m_Vertices.end(); iter++)
        delete *iter;
    m_Vertices.clear();
    for (auto iter = m_Normals.begin(); iter != m_Normals.end(); iter++)
        delete *iter;
    m_Normals.clear();
    for (auto iter = m_Uvs.begin(); iter != m_Uvs.end(); iter++)
        delete *iter;
    m_Uvs.clear();
    m_Triangles.clear();
}
