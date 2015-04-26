#include "SREngine.h"
#include "ModelFactory.h"

SREngine::~SREngine()
{
    ShutDown();
}

void SREngine::GetTimeOfDay(struct timeval *tp, void* tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
}

void SREngine::Init()
{
    m_Camera = new Camera();
    m_Camera->Transform->SetPosition(0, 0, -10);
    m_Camera->UpdateMatrix();
    m_Camera->SetNearClipPlane(1);
    m_Camera->SetFarClipPlane(50);
    m_Target = ModelFactory::GetCube();
}

void SREngine::Update()
{
    struct timeval tv;
    GetTimeOfDay(&tv, NULL);
    unsigned int now = tv.tv_sec * 1000000 + tv.tv_usec;
    if ((now - m_LastTime) > m_AnimationInterval)
    {
        m_LastTime = now;
        m_Camera->Render(m_Target);
    }
    else
    {
        Sleep(0);
    }
}

void SREngine::ShutDown()
{
    delete m_Camera;
    m_Camera = nullptr;
    delete m_Target;
    m_Target = nullptr;
}
