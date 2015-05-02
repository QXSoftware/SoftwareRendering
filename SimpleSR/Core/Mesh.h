#ifndef Mesh_h__
#define Mesh_h__

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Transform.h>
#include <Matrix4x4.h>
#include <Mathf.h>
#include <Color.h>
#include <ColorBuffer.h>
#include <DepthBuffer.h>
#include <DirectionalLight.h>
#include <windows.h>
#include <vector>
#include <Texture2D.h>
#include <Vertex.h>
#include <MacrosAndDefines.h>

class Mesh
{
    friend class ModelParser;
    friend class ModelFactory;
    std::vector<Vector3*> m_Vertices;
    std::vector<Vector3*> m_Normals;
    std::vector<Vector2*> m_Uvs;
    std::vector<int> m_Triangles;
    DirectionalLight* m_DirectionalLight;
    Texture2D* m_Texture;
    Color m_AmbientColor;

    inline bool InsidePlane(const Vertex& v, RegionCode plane)
    {
        return (v.Code & plane) == 0;
    };
    Vertex ComputeIntersect(Vertex& v0, Vertex& v1, RegionCode plane);
    Vertex ConstructVertex(Vector4& v, Vector4& n, Vector2& uv, const Matrix4x4& mvp, const Matrix4x4& mv, const Matrix4x4& obj2wi);
    std::vector<Vertex> PreClip(Vertex v0, Vertex v1, Vertex v2);
    void Clip(Vertex v0, Vertex v1, Vertex v2, ColorBuffer* cBuf, DepthBuffer* dBuf, const Matrix4x4& vp);
public:
    Mesh();
    ~Mesh();
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
public:
    Transform* Transform;
public:
    void SetLight(DirectionalLight* l, Color a);
    void Render(ColorBuffer* cBuf, DepthBuffer* dBuf, const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp);
    void Clear();
};

#endif // Mesh_h__
