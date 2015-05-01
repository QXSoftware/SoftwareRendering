#ifndef Vertex_h__
#define Vertex_h__

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Color.h>
#include <MacrosAndDefines.h>

struct Vertex
{
    Vector4 Pos;
    Vector4 PosWorld;
    Vector4 Normal;
    Vector3 NormalWorld;
    Vector2 UV;
    Color DiffCol;
    Color VertexCol;

    RegionCode Code;
    float BoundaryCode[6];

    Vertex(Vector3 pos, Vector3 n, Vector2 uv);
    Vertex();
    ~Vertex() = default;
};

#endif // Vertex_h__
