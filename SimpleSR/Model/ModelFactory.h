#ifndef ModelFactory_h__
#define ModelFactory_h__

#include <Mesh.h>
#include <Vector3.h>
#include <ModelParser.h>

class ModelFactory
{
public:
    ModelFactory() = delete;
    ~ModelFactory() = delete;
public:
    static tstring GetBaseDir();
    static Mesh* GetTriangle();
    static Mesh* GetQuad();
    static Mesh* GetCube();
    static Mesh* GetCapsule();
    static Mesh* GetCylinder();
    static Mesh* GetSphere();
};

#endif // ModelFactory_h__
