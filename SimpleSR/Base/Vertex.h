#ifndef Vertex_h__
#define Vertex_h__

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

struct Vertex
{
    Vector4 PosWorld;
    Vector4 Pos;
    Vector3 Normal;
    Vector2 UV0;
};

#endif // Vertex_h__
