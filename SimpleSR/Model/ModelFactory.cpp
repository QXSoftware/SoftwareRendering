#include <ModelFactory.h>
#include <windows.h>
#include <tchar.h>

Mesh* ModelFactory::GetTriangle()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(path.append(_T("/FBX/Triangle")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 0, 0);
    return mesh;
}

Mesh* ModelFactory::GetQuad()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(path.append(_T("/FBX/Quad")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}

Mesh* ModelFactory::GetCube()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(path.append(_T("/FBX/Cube")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}

Mesh* ModelFactory::GetCapsule()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(path.append(_T("/FBX/Capsule")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}

Mesh* ModelFactory::GetCylinder()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    std::wstring path(dir);
    auto mesh = ModelParser::Parse(path.append(_T("/FBX/Cylinder")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}
