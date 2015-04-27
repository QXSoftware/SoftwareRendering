#ifndef Vertex_h__
#define Vertex_h__

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Color.h>

struct Vertex
{
    Vector4 Pos;
    Vector4 PosWorld;
    Vector4 Normal;
    Vector3 NormalWorld;
    Vector2 UV0;
    Color DiffCol;
    Color VertexCol;

    Vertex(Vector3 pos, Vector3 n, Vector2 uv0);
    Vertex() = default;
    ~Vertex() = default;
};

#endif // Vertex_h__
