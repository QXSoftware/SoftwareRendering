#ifndef ModelFactory_h__
#define ModelFactory_h__

#include "Mesh.h"
#include "Vector3.h"

class ModelFactory
{
public:
    ModelFactory() = delete;
    ~ModelFactory() = delete;
public:
    static Mesh* GetQuad();
};

#endif // ModelFactory_h__
