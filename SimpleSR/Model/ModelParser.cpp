#include <ModelParser.h>
#include <windows.h>
#include <tchar.h>

Mesh* ModelParser::Parse(const std::wstring& path)
{
    auto mesh = new Mesh();
    std::wifstream infile(path, std::ios::in);
    TCHAR buff[100];
    int step = 0;
    while (infile.getline(buff, 100))
    {
        if (std::wstring(buff) == _T("#vertices"))
        {
            step = 1;
            continue;
        }
        else if (std::wstring(buff) == _T("#triangles"))
        {
            step = 2;
            continue;
        }
        else if (std::wstring(buff) == _T("#normals"))
        {
            step = 3;
            continue;
        }
        else if (std::wstring(buff) == _T("#uvs"))
        {
            step = 4;
            continue;
        }
        else if (std::wstring(buff).empty())
        {
            continue;
        }
        switch (step)
        {
            case 1:
            {
                TCHAR* pEnd;
                float x, y, z;
                x = std::wcstof(buff, &pEnd);
                pEnd++;
                y = std::wcstof(pEnd, &pEnd);
                pEnd++;
                z = std::wcstof(pEnd, NULL);
                auto v = new Vector3(x, y, z);
                mesh->m_Vertices.push_back(v);
                break;
            }
            case 2:
            {
                float x;
                x = std::wcstof(buff, NULL);
                mesh->m_Triangles.push_back((int)x);
                break;
            }
            case 3:
            {
                TCHAR* pEnd;
                float x, y, z;
                x = std::wcstof(buff, &pEnd);
                pEnd++;
                y = std::wcstof(pEnd, &pEnd);
                pEnd++;
                z = std::wcstof(pEnd, NULL);
                auto v = new Vector3(x, y, z);
                mesh->m_Normals.push_back(v);
                break;
            }
            case 4:
            {
                TCHAR* pEnd;
                float x, y;
                x = std::wcstof(buff, &pEnd);
                pEnd++;
                y = std::wcstof(pEnd, &pEnd);
                auto v = new Vector2(x, y);
                mesh->m_Uvs.push_back(v);
                break;
            }
        }
    }
    infile.close();
    return mesh;
}
