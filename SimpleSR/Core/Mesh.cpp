#include "Mesh.h"
#include "DrawingTool.h"

Mesh::Mesh()
    :Transform(new ::Transform())
{}

Mesh::~Mesh()
{
    Clear();
}

void Mesh::Render(const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp)
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
            ProcessTriangle(triangle, mvp, vp);
        }
    }
}

void Mesh::ProcessTriangle(Vector3** triangle, const Matrix4x4& mvp, const Matrix4x4& vp)
{
    auto v0 = vp * mvp * Vector4(*triangle[0], 1);
    auto v1 = vp * mvp * Vector4(*triangle[1], 1);
    auto v2 = vp * mvp * Vector4(*triangle[2], 1);
    DrawingTool::DrawLine(v0.x, v0.y, v1.x, v1.y, Color::red);
    DrawingTool::DrawLine(v0.x, v0.y, v2.x, v2.y, Color::red);
    DrawingTool::DrawLine(v2.x, v2.y, v1.x, v1.y, Color::red);
}

void Mesh::Clear()
{
    m_Vertices.clear();
    m_Normals.clear();
    m_Uvs.clear();
    m_Triangles.clear();
}
