#include <Mesh.h>
#include <Triangle.h>

Mesh::Mesh()
    :Transform(new ::Transform())
{}

Mesh::~Mesh()
{
    Clear();
}

void Mesh::SetLight(DirectionalLight* l, Color a)
{
    m_DirectionalLight = l;
    m_AmbientColor = a;
}

void Mesh::Render(ColorBuffer* cBuf, DepthBuffer* dBuf, const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp)
{
    auto obj2w = Transform->LocalToWorldMatrix();
    auto obj2wi = Transform->WorldToLocalMatrix();
    auto mvp = p * v * obj2w;

    Vector3* normal[3];
    Vector3* vertex[3];
    Vector2* uv0[3];
    auto i = 0;
    for (auto iter = m_Triangles.begin(); iter != m_Triangles.end(); iter++)
    {
        vertex[i] = m_Vertices[*iter];
        normal[i] = m_Normals[*iter];
        uv0[i] = m_Uvs[*iter];
        i++;
        if (i > 2)
        {
            i = 0;

            Triangle tr;
            Vertex v0(*vertex[0], *normal[0], *uv0[0]);
            Vertex v1(*vertex[1], *normal[1], *uv0[1]);
            Vertex v2(*vertex[2], *normal[2], *uv0[2]);
            tr.SetVertices(&v0, &v1, &v2);
            tr.SetBuffers(cBuf, dBuf);
            tr.SetMatrixes(&obj2w, &obj2wi, const_cast<Matrix4x4*>(&v), const_cast<Matrix4x4*>(&p), const_cast<Matrix4x4*>(&vp), &mvp);
            tr.SetLight(m_DirectionalLight, m_AmbientColor);
            tr.Render();
        }
    }
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
