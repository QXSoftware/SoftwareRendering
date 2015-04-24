#ifndef Screen_h__
#define Screen_h__

#include <windows.h>

extern HWND g_MainWindowHwnd;

#define DEFAULT_SCREEN_WIDTH  800
#define DEFAULT_SCREEN_HEIGHT 600

class Screen
{
    int m_Height;
    int m_Width;
    Screen()
        :m_Width(DEFAULT_SCREEN_WIDTH), m_Height(DEFAULT_SCREEN_HEIGHT)
    {}
    ~Screen() = default;
public:
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;
    static Screen* const current;
public:
    void UpdateScreenSize();
    inline int GetScreenWidth()
    {
        return m_Width;
    }
    inline int GetScreenHeight()
    {
        return m_Height;
    }
    inline int GetSystemMetricsWidth()
    {
        return GetSystemMetrics(SM_CXSCREEN);
    }
    inline int GetSystemMetricsHeight()
    {
        return GetSystemMetrics(SM_CYSCREEN);
    }
    inline float GetAspect()
    {
        return  (float)m_Width / (float)m_Height;
    }
};

#endif // Screen_h__
