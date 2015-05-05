#ifndef SREngine_h__
#define SREngine_h__

#include <Camera.h>
#include <windows.h>
#include <time.h>
#include <vector>

class SREngine
{
    Camera* m_Camera;
    std::vector<Mesh*> m_Target;

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
    inline std::vector<Mesh*> GetTarget() const
    {
        return m_Target;
    }
    void Init();
    void Update();
    void ShutDown();
};

#endif // SREngine_h__
