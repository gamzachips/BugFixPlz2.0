#include "pch.h"
#include "Window.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

Window::Window(const WindowDesc& _desc)
{
    hInstance = _desc.instance;
    cmdShow = _desc.cmdShow;
    wcscpy_s(szTitle, MAX_LOADSTRING, _desc.title);
    wcscpy_s(szWindowClass, MAX_LOADSTRING, _desc.windowClass);
    hIcon = _desc.icon;
    hIconSmall = _desc.iconSmall;
}

Window::~Window()
{
}


ATOM Window::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = hIcon ? hIcon : LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = hIconSmall ? hIconSmall : LoadIcon(nullptr, IDI_APPLICATION);

    int ret = RegisterClassExW(&wcex);
    return ret;
}


BOOL Window::InitInstance(HINSTANCE _hInstance, int _nCmdShow)
{
    hInstance = _hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, _nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


int Window::Initialize()
{

    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, cmdShow))
    {
        return FALSE;
    }
    return TRUE;

}

bool Window::Update()
{

    // �⺻ �޽��� �����Դϴ�:
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false; 

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

int Window::Destroy()
{
    return (int)msg.wParam;
}
