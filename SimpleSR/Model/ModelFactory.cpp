#include <ModelFactory.h>
#include <windows.h>
#include <MacrosAndDefines.h>

tstring ModelFactory::GetBaseDir()
{
    TCHAR dir[255];
    GetCurrentDirectory(255, dir);
    tstring path(dir);
    return path;
}

Mesh* ModelFactory::GetTriangle()
{
    auto mesh = ModelParser::Parse(GetBaseDir().append(_T("/FBX/Triangle")));
    mesh->m_Texture = Texture2D::Load(GetBaseDir().append(_T("/Texture/baby.bmp")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 0, 0);
    return mesh;
}

Mesh* ModelFactory::GetQuad()
{
    auto mesh = ModelParser::Parse(GetBaseDir().append(_T("/FBX/Quad")));
    mesh->m_Texture = Texture2D::Load(GetBaseDir().append(_T("/Texture/baby.bmp")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}

Mesh* ModelFactory::GetCube()
{
    auto mesh = ModelParser::Parse(GetBaseDir().append(_T("/FBX/Cube")));
    mesh->m_Texture = Texture2D::Load(GetBaseDir().append(_T("/Texture/baby.bmp")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}

Mesh* ModelFactory::GetCapsule()
{
    auto mesh = ModelParser::Parse(GetBaseDir().append(_T("/FBX/Capsule")));
    mesh->m_Texture = Texture2D::Load(GetBaseDir().append(_T("/Texture/baby.bmp")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}

Mesh* ModelFactory::GetCylinder()
{
    auto mesh = ModelParser::Parse(GetBaseDir().append(_T("/FBX/Cylinder")));
    mesh->m_Texture = Texture2D::Load(GetBaseDir().append(_T("/Texture/baby.bmp")));
    mesh->Transform->SetPosition(0, 0, 0);
    mesh->Transform->SetRotation(0, 60, 0);
    return mesh;
}
