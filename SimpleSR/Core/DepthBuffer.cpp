#include <DepthBuffer.h>

DepthBuffer::DepthBuffer(int w, int h)
    :m_Width(w), m_Height(h)
{
    m_Buffer = new float*[m_Width];
    for (auto i = 0; i < m_Width; i++)
    {
        m_Buffer[i] = new float[m_Height];
    }
    Clear(0);
}

DepthBuffer::~DepthBuffer()
{
    for (auto i = 0; i < m_Width; i++)
    {
        delete[] m_Buffer[i];
    }
    delete[] m_Buffer;
    m_Buffer = nullptr;
}

bool DepthBuffer::ZTest(int x, int y, float d)
{
    if (x < m_Width && y < m_Height)
    {
        return m_Buffer[x][y] >= d;
    }
    return false;
}

void DepthBuffer::SetDepth(int x, int y, float d)
{
    m_Buffer[x][y] = d;
}

void DepthBuffer::Clear(float d)
{
    for (auto i = 0; i < m_Width; i++)
    {
        for (auto j = 0; j < m_Height; j++)
        {
            m_Buffer[i][j] = d;
        }
    }
}
