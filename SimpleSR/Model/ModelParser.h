#ifndef ModelParser_h__
#define ModelParser_h__

#include <string>
#include <fstream>
#include <Mesh.h>
#include <MacrosAndDefines.h>

class ModelParser
{
public:
    static Mesh* Parse(const tstring& path);
};

#endif // ModelParser_h__
