#include "Screen.h"

Screen* const Screen::current = new Screen();

void Screen::UpdateScreenSize()
{
    RECT rect;
    if (GetWindowRect(g_MainWindowHwnd, &rect))
    {
        m_Width = rect.right - rect.left;
        m_Height = rect.bottom - rect.top;
    }
}
