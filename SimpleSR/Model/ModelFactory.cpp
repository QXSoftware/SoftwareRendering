#include "ModelFactory.h"

Mesh* ModelFactory::GetQuad()
{
    auto mesh = new Mesh();
    mesh->m_Vertices.push_back(new Vector3(-0.500, -0.500, 0));
    mesh->m_Vertices.push_back(new Vector3(0.500, 0.500, 0));
    mesh->m_Vertices.push_back(new Vector3(0.500, -0.500, 0));
    mesh->m_Normals.push_back(new Vector3(0, 0, -1));
    mesh->m_Normals.push_back(new Vector3(0, 0, -1));
    mesh->m_Normals.push_back(new Vector3(0, 0, -1));
    mesh->m_Triangles.push_back(0);
    mesh->m_Triangles.push_back(1);
    mesh->m_Triangles.push_back(2);

    mesh->Transform->SetPosition(0, 0, 20);
    mesh->Transform->SetRotation(0, 0, 20);

    return mesh;
}
