#ifndef Vertex_h__
#define Vertex_h__

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Color.h>
#include <MacrosAndDefines.h>

struct Vertex
{
    Vector4 Pos;//������꣬͸��ͶӰ��͸�ӳ���ǰ
    float W;//�������ϵ��1/z
    Vector2 UV;
    Color DiffCol;//���������

    RegionCode Code;

    Vertex();
    ~Vertex() = default;
};

#endif // Vertex_h__
