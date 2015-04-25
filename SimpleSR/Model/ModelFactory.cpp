#include "ModelFactory.h"
#include <windows.h>
#include <tchar.h>

Mesh* ModelFactory::GetQuad()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(_T("/FBX/Quad"));
    mesh->Transform->SetPosition(0, 0, 5);
    return mesh;
}

Mesh* ModelFactory::GetCube()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(path.append(_T("/FBX/Cube")));
    mesh->Transform->SetPosition(0, 0, 3);
    return mesh;
}
