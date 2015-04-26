#ifndef SREngine_h__
#define SREngine_h__

#include <Camera.h>
#include <windows.h>
#include <time.h>

class SREngine
{
    Camera* m_Camera;
    Mesh* m_Target;

    unsigned int m_LastTime;
    unsigned int m_AnimationInterval = (unsigned int)(1000000.0f / 60.0f);
    void GetTimeOfDay(struct timeval *tp, void* tzp);
public:
    SREngine() = default;
    ~SREngine();
    SREngine(const SREngine&) = delete;
    SREngine& operator=(const SREngine&) = delete;
public:
    inline Camera* GetCamera()
    {
        return m_Camera;
    }
    inline Mesh* GetTarget()
    {
        return m_Target;
    }
    void Init();
    void Update();
    void ShutDown();
};

#endif // SREngine_h__
