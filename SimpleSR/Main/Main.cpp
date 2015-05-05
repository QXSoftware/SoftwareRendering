#include <Main.h>

#define MAX_LOADSTRING 100

TCHAR g_Title[MAX_LOADSTRING];            // 标题栏文本
TCHAR g_WindowClass[MAX_LOADSTRING];      // 主窗口类名
HWND g_MainWindowHwnd;                    // 主窗口句柄

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
SREngine g_Engine;

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

    g_Engine.Init();

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLESR));

    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        g_Engine.Update();
    }

    g_Engine.ShutDown();

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
            auto cam = g_Engine.GetCamera();
            if ((_TCHAR)wParam == 'W')
            {
                cam->SetTranslationDelta(Vector3::up * delta);
            }
            else if ((_TCHAR)wParam == 'S')
            {
                cam->SetTranslationDelta(Vector3::down * delta);
            }
            else if ((_TCHAR)wParam == 'A')
            {
                cam->SetTranslationDelta(Vector3::left * delta);
            }
            else if ((_TCHAR)wParam == 'D')
            {
                cam->SetTranslationDelta(Vector3::right * delta);
            }
            else if ((_TCHAR)wParam == 'E')
            {
                cam->SetTranslationDelta(Vector3::forward * delta);
            }
            else if ((_TCHAR)wParam == 'Q')
            {
                cam->SetTranslationDelta(Vector3::backward * delta);
            }
            else if ((_TCHAR)wParam == VK_LEFT)
            {
                cam->SetRotationDelta(Vector3::up * delta);
            }
            else if ((_TCHAR)wParam == VK_RIGHT)
            {
                cam->SetRotationDelta(Vector3::down * delta);
            }
            else if ((_TCHAR)wParam == VK_UP)
            {
                cam->SetRotationDelta(Vector3::right * delta);
            }
            else if ((_TCHAR)wParam == VK_DOWN)
            {
                cam->SetRotationDelta(Vector3::left * delta);
            }
            else if ((_TCHAR)wParam == VK_ESCAPE)
            {
                auto target = cam->Transform;
                target->SetPosition(0, 0, -10);
                target->SetRotation(0, 0, 0);
            }
            break;
        }
        case WM_KEYUP:
        {
            auto cam = g_Engine.GetCamera();
            cam->ResetTranslationDelta();
            cam->ResetRotationDelta();
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
