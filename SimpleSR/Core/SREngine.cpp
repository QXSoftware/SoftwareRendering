#include <SREngine.h>
#include <ModelFactory.h>
#include <StatusTool.h>
#include <SRTime.h>

StatusTool g_StatusTool;

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
    m_Camera->SetNearClipPlane(1);
    m_Camera->SetFarClipPlane(50);
    g_StatusTool.SetColorBuffer(m_Camera->m_ColorBuffer);

    m_Target.push_back(ModelFactory::GetCube());
    m_Target.push_back(ModelFactory::GetCylinder());
    m_Target.push_back(ModelFactory::GetCapsule());
}

void SREngine::Update()
{
    struct timeval tv;
    GetTimeOfDay(&tv, NULL);
    unsigned int now = tv.tv_sec * 1000000 + tv.tv_usec;
    SRTime::DeltaTime = (now - m_LastTime) / 1000000.0f;
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
    for (auto mesh : m_Target)
    {
        delete mesh;
    }
    m_Target.clear();
}
