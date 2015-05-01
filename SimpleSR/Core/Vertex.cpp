#include <Vertex.h>

Vertex::Vertex()
    :Code(0)
{}

Vertex::Vertex(Vector3 pos, Vector3 n, Vector2 uv)
    : Code(0)
{
    Pos = Vector4(pos, 1);
    Normal = n;
    UV = uv;
}
