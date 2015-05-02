#include <Main.h>

#define MAX_LOADSTRING 100

TCHAR g_Title[MAX_LOADSTRING];            // 标题栏文本
TCHAR g_WindowClass[MAX_LOADSTRING];      // 主窗口类名
HWND g_MainWindowHwnd;                    // 主窗口句柄

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
SREngine engine;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    HACCEL hAccelTable;

    LoadString(hInstance, IDS_APP_TITLE, g_Title, MAX_LOADSTRING);
    LoadString(hInstance, IDC_SIMPLESR, g_WindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    engine.Init();

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLESR));

    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        engine.Update();
    }

    engine.ShutDown();

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLESR));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_SIMPLESR);
    wcex.lpszClassName = g_WindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    auto winWidth = Screen::current->GetScreenWidth();
    auto winHeight = Screen::current->GetScreenHeight();
    auto scrWidth = Screen::current->GetSystemMetricsWidth();
    auto scrHeight = Screen::current->GetSystemMetricsHeight();

    HWND hWnd = CreateWindow(g_WindowClass, g_Title, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        (scrWidth - winWidth) / 2, (scrHeight - winHeight) / 2, winWidth, winHeight, NULL, NULL, hInstance, NULL);
    g_MainWindowHwnd = hWnd;

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            auto delta = 0.3f;
            if ((_TCHAR)wParam == 'W')
            {
                auto target = engine.GetCamera()->Transform;
                auto pos = target->GetPosition();
                target->SetPosition(pos.x, pos.y + delta, pos.z);
            }
            else if ((_TCHAR)wParam == 'S')
            {
                auto target = engine.GetCamera()->Transform;
                auto pos = target->GetPosition();
                target->SetPosition(pos.x, pos.y - delta, pos.z);
            }
            else if ((_TCHAR)wParam == 'A')
            {
                auto target = engine.GetCamera()->Transform;
                auto pos = target->GetPosition();
                target->SetPosition(pos.x - delta, pos.y, pos.z);
            }
            else if ((_TCHAR)wParam == 'D')
            {
                auto target = engine.GetCamera()->Transform;
                auto pos = target->GetPosition();
                target->SetPosition(pos.x + delta, pos.y, pos.z);
            }
            else if ((_TCHAR)wParam == 'E')
            {
                auto target = engine.GetCamera()->Transform;
                auto pos = target->GetPosition();
                target->SetPosition(pos.x, pos.y, pos.z + delta);
            }
            else if ((_TCHAR)wParam == 'Q')
            {
                auto target = engine.GetCamera()->Transform;
                auto pos = target->GetPosition();
                target->SetPosition(pos.x, pos.y, pos.z - delta);
            }
            else if ((_TCHAR)wParam == VK_LEFT)
            {
                auto target = engine.GetCamera()->Transform;
                auto rot = target->GetRotation();
                target->SetRotation(rot.x, rot.y + delta * 10, rot.z);
            }
            else if ((_TCHAR)wParam == VK_RIGHT)
            {
                auto target = engine.GetCamera()->Transform;
                auto rot = target->GetRotation();
                target->SetRotation(rot.x, rot.y - delta * 10, rot.z);
            }
            else if ((_TCHAR)wParam == VK_UP)
            {
                auto target = engine.GetCamera()->Transform;
                auto rot = target->GetRotation();
                target->SetRotation(rot.x + delta * 10, rot.y, rot.z);
            }
            else if ((_TCHAR)wParam == VK_DOWN)
            {
                auto target = engine.GetCamera()->Transform;
                auto rot = target->GetRotation();
                target->SetRotation(rot.x - delta * 10, rot.y, rot.z);
            }
            else if ((_TCHAR)wParam == VK_ESCAPE)
            {
                auto target = engine.GetCamera()->Transform;
                target->SetPosition(0, 0, -10);
            }
            break;
        }
        case WM_ERASEBKGND:
        case WM_PAINT:
        {
            return (LRESULT)1;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}
