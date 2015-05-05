#include <StatusTool.h>
#include <MacrosAndDefines.h>
#include <SRTime.h>

StatusTool::StatusTool()
    :m_ColorBuffer(0)
{}

void StatusTool::SetColorBuffer(ColorBuffer* cb)
{
    m_ColorBuffer = cb;
}

void StatusTool::DrawDebug(int x, int y, tstring s)
{
    auto len = s.length();
    RECT rect{ x, y, x + 1000, y + 50 };
    DrawText(m_ColorBuffer->m_MemoryDC, s.c_str(), len, &rect, DT_LEFT);
}

void StatusTool::DrawFPS()
{
    tstringstream ss;
    ss.precision(4);
    ss << "FPS:" << 1.0f / SRTime::DeltaTime;
    DrawDebug(5, 5, ss.str());
}
