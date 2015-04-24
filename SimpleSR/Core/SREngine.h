#ifndef SREngine_h__
#define SREngine_h__

#include "Camera.h"

class SREngine
{
    Camera* m_Camera;
    Mesh* m_Target;
public:
    SREngine() = default;
    ~SREngine();
    SREngine(const SREngine&) = delete;
    SREngine& operator=(const SREngine&) = delete;
public:
    void Init();
    void Update();
    void ShutDown();
};

#endif // SREngine_h__
