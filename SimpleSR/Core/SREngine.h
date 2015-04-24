#ifndef SREngine_h__
#define SREngine_h__

#include "Camera.h"

class SREngine
{
    const Camera* m_Camera;
public:
    SREngine();
    ~SREngine();
    SREngine(const SREngine&) = delete;
    SREngine& operator=(const SREngine&) = delete;
public:
    void Init();
    void Update();
    void ShutDown();
};

#endif // SREngine_h__
