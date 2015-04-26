#ifndef __DepthBuffer_h__
#define __DepthBuffer_h__

class DepthBuffer
{
    float** m_Buffer;
    int m_Width;
    int m_Height;
public:
    DepthBuffer(int w, int h);
    ~DepthBuffer();
    DepthBuffer(const DepthBuffer&) = delete;
    DepthBuffer& operator=(const DepthBuffer&) = delete;
public:
    float GetDepth(int x, int y);
    void SetDepth(int x, int y, float d);
    void Clear(float d);
};

#endif // __DepthBuffer_h__
