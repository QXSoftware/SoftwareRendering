#ifndef ModelParser_h__
#define ModelParser_h__

#include <string>
#include <fstream>
#include <Mesh.h>

class ModelParser
{
public:
    static Mesh* Parse(const std::wstring& path);
};

#endif // ModelParser_h__
