#include <Vertex.h>

Vertex::Vertex(Vector3* pos, Vector3* n, Vector2* uv0)
{
    Pos = Vector4(*pos, 1);
    Normal = *n;
    UV0 = *uv0;
}
