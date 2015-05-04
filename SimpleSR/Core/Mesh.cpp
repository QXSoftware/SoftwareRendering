#include <Mesh.h>
#include <Triangle.h>
#include <MacrosAndDefines.h>

Mesh::Mesh()
    :m_DirectionalLight(0), m_Texture(0)
{
    Transform = new ::Transform();
}

Mesh::~Mesh()
{
    Clear();
}

void Mesh::SetLight(DirectionalLight* l, Color a)
{
    m_DirectionalLight = l;
    m_AmbientColor = a;
}

Vertex Mesh::ComputeIntersect(Vertex& v0, Vertex& v1, RegionCode plane)
{
    float u = 0;
    Vector4& in = v0.Pos;
    Vector4& out = v1.Pos;
    switch (plane)
    {
        case CVV_LEFT:
        {
            u = (in.x + in.w) / (in.x + in.w - out.x - out.w);
            break;
        }
        case CVV_RIGHT:
        {
            u = (in.x - in.w) / (in.x - in.w - out.x + out.w);
            break;
        }
        case CVV_BOTTOM:
        {
            u = (in.y + in.w) / (in.y + in.w - out.y - out.w);
            break;
        }
        case CVV_TOP:
        {
            u = (in.y - in.w) / (in.y - in.w - out.y + out.w);
            break;
        }
        case CVV_NEAR:
        {
            u = (in.z + in.w) / (in.z + in.w - out.z - out.w);
            break;
        }
        case CVV_FAR:
        {
            u = (in.z - in.w) / (in.z - in.w - out.z + out.w);
            break;
        }
    }
    return Mathf::Lerp(v0, v1, u);
}

Vertex Mesh::ConstructVertex(Vector4& v, Vector4& n, Vector2& uv, const Matrix4x4& mvp, const Matrix4x4& mv, const Matrix4x4& obj2wi)
{
    Vertex vert;
    vert.Pos = mvp * v;
    vert.W = 1.0f / (mv * v).z;
    vert.UV = uv;
    // 光照计算
    auto normal = Vector3(n * obj2wi).normalized();
    vert.DiffCol = Mathf::Max(0, Vector3::Dot(normal, m_DirectionalLight->Direction))
        * m_DirectionalLight->Intensity * m_DirectionalLight->Col;
    // 计算区域码
    vert.Code = Mathf::Encode(vert.Pos);
    return vert;
}

std::vector<Vertex> Mesh::PreClip(Vertex v0, Vertex v1, Vertex v2)
{
    std::vector<Vertex> input{ v0, v1, v2 };
    std::vector<Vertex> output;

    Vertex s = input.back();
    auto prev = s.Pos.w < W_CLIPPING_PLANE ? -1 : 1;
    for (auto e : input)
    {
        auto cur = e.Pos.w < W_CLIPPING_PLANE ? -1 : 1;
        if (prev * cur < 0)
        {
            auto t = (W_CLIPPING_PLANE - s.Pos.w) / (e.Pos.w - s.Pos.w);
            output.push_back(Mathf::Lerp(s, e, t));
        }
        if (cur > 0)
        {
            output.push_back(e);
        }
        prev = cur;
        s = e;
    }
    return output;
}

void Mesh::Clip(Vertex v0, Vertex v1, Vertex v2, ColorBuffer* cBuf, DepthBuffer* dBuf, const Matrix4x4& vp)
{
    auto clipPlanes =
    {
        CVV_LEFT,
        CVV_RIGHT,
        CVV_BOTTOM,
        CVV_TOP,
        CVV_NEAR,
        CVV_FAR,
    };

    // 裁剪 w 小于 W_CLIPPING_PLANE 的齐次坐标
    auto output = PreClip(v0, v1, v2);
    if (output.size() < 3)
        return;

    // cvv 裁剪
    for (RegionCode plane : clipPlanes)
    {
        std::vector<Vertex> input = output;
        output.clear();
        if (input.empty())
            continue;
        Vertex s = input.back();
        for (Vertex e : input)
        {
            if (InsidePlane(e, plane))
            {
                if (!InsidePlane(s, plane))
                {
                    output.push_back(ComputeIntersect(e, s, plane));
                }
                output.push_back(e);
            }
            else if (InsidePlane(s, plane))
            {
                output.push_back(ComputeIntersect(s, e, plane));
            }
            s = e;
        }
    }

    if (output.size() < 3)
        return;

    // 渲染裁剪完毕的三角形
    for (int i = 0, max = output.size() - 2; i < max; i++)
    {
        auto out0 = output[0];
        auto out1 = output[i + 1];
        auto out2 = output[i + 2];
        Triangle tr;
        tr.m_V0 = &out0;
        tr.m_V1 = &out1;
        tr.m_V2 = &out2;
        tr.m_ColorBuf = cBuf;
        tr.m_DepthBuf = dBuf;
        tr.m_ViewPortMatrix = const_cast<Matrix4x4*>(&vp);
        tr.m_Texture = m_Texture;
        tr.m_AmbientColor = m_AmbientColor;
        tr.Render();
    }
}

void Mesh::Render(ColorBuffer* cBuf, DepthBuffer* dBuf, const Matrix4x4&p, const Matrix4x4&v, const Matrix4x4& vp)
{
    auto obj2w = Transform->LocalToWorldMatrix();
    auto obj2wi = Transform->WorldToLocalMatrix();
    auto mv = v * obj2w;
    auto mvp = p * mv;

    Vector3* normal[3];
    Vector3* vertex[3];
    Vector2* uv[3];
    auto i = 0;
    for (auto iter = m_Triangles.begin(); iter != m_Triangles.end(); iter++)
    {
        vertex[i] = m_Vertices[*iter];
        normal[i] = m_Normals[*iter];
        uv[i] = m_Uvs[*iter];
        i++;
        if (i > 2)
        {
            i = 0;

            // Cull Back
            if (Mathf::IsBackface(vertex[0], vertex[1], vertex[2], &mvp, const_cast<Matrix4x4*>(&vp)))
                continue;

            auto v0 = ConstructVertex(Vector4(*vertex[0], 1), Vector4(*normal[0]), *uv[0], mvp, mv, obj2wi);
            auto v1 = ConstructVertex(Vector4(*vertex[1], 1), Vector4(*normal[1]), *uv[1], mvp, mv, obj2wi);
            auto v2 = ConstructVertex(Vector4(*vertex[2], 1), Vector4(*normal[2]), *uv[2], mvp, mv, obj2wi);

            Clip(v0, v1, v2, cBuf, dBuf, vp);
        }
    }
}

void Mesh::Clear()
{
    for (auto iter = m_Vertices.begin(); iter != m_Vertices.end(); iter++)
        delete *iter;
    m_Vertices.clear();
    for (auto iter = m_Normals.begin(); iter != m_Normals.end(); iter++)
        delete *iter;
    m_Normals.clear();
    for (auto iter = m_Uvs.begin(); iter != m_Uvs.end(); iter++)
        delete *iter;
    m_Uvs.clear();
    m_Triangles.clear();
    delete m_Texture;
    m_Texture = nullptr;
    delete Transform;
    Transform = nullptr;
}
