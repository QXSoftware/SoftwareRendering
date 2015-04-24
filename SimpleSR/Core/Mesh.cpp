#include "Mesh.h"

Mesh::Mesh()
    :Transform(new ::Transform())
{}

Mesh::~Mesh()
{
    Clear();
}

void Mesh::Clear()
{
    delete m_Vertices;
    m_Vertices = nullptr;
    delete m_Normals;
    m_Normals = nullptr;
    delete m_Uvs;
    m_Uvs = nullptr;
    delete m_Triangles;
    m_Triangles = nullptr;
    delete Transform;
    Transform = nullptr;
}
