#ifndef Mesh_h__
#define Mesh_h__

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Mathf.h"
#include "Color.h"
#include "DirectionalLight.h"
#include <windows.h>
#include <vector>

class Mesh
{
    friend class ModelParser;
    friend class ModelFactory;
    std::vector<Vector3*> m_Vertices;
    std::vector<Vector3*> m_Normals;
    std::vector<Vector2*> m_Uvs;
    std::vector<int> m_Triangles;
    void ProcessTriangle(HDC dc, Vector3** triangle, const Matrix4x4& mvp, const Matrix4x4& vp);
    Color ComputeColor(const DirectionalLight& d, const Color& a, const Vector3& n);
public:
    Mesh();
    ~Mesh();
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
public:
    Transform* Transform;
public:
    void Render(HDC dc, const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp);
    void Clear();
};

#endif // Mesh_h__
