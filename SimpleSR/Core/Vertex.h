#ifndef Vertex_h__
#define Vertex_h__

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Color.h>
#include <MacrosAndDefines.h>

struct Vertex
{
    Vector4 Pos;//齐次坐标，透视投影后，透视除法前
    float W;//相机坐标系，1/z
    Vector2 UV;
    Color DiffCol;//漫反射光照

    RegionCode Code;

    Vertex();
    ~Vertex() = default;
};

#endif // Vertex_h__
