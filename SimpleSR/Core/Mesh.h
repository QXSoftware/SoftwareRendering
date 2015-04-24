#ifndef Mesh_h__
#define Mesh_h__

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Mathf.h"

class Mesh
{
    Vector3* m_Vertices;
    Vector3* m_Normals;
    Vector2* m_Uvs;
    int* m_Triangles;
public:
    Mesh();
    ~Mesh();
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
public:
    Transform* Transform;
public:
    void Clear();
};

#endif // Mesh_h__
