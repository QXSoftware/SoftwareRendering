#ifndef Mesh_h__
#define Mesh_h__

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Mathf.h"
#include <vector>

class Mesh
{
    friend class ModelFactory;
    std::vector<Vector3*> m_Vertices;
    std::vector<Vector3*> m_Normals;
    std::vector<Vector2*> m_Uvs;
    std::vector<int> m_Triangles;
    void ProcessTriangle(Vector3** triangle, const Matrix4x4& mvp, const Matrix4x4& vp);
public:
    Mesh();
    ~Mesh();
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
public:
    Transform* Transform;
public:
    void Render(const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp);
    void Clear();
};

#endif // Mesh_h__
