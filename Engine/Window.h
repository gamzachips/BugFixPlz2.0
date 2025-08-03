#pragma once

#include <SDKDDKVer.h>
#include <windows.h>

#define MAX_LOADSTRING 100


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

struct WindowDesc
{
	HINSTANCE instance;
	int cmdShow;
	const WCHAR* title;
	const WCHAR* windowClass;
	HICON icon;
	HICON iconSmall;
};

class Window
{
public:
	Window(const WindowDesc& _desc);
	~Window();

	int Initialize();
	bool Update();
	int Destroy();

private:
	ATOM MyRegisterClass(HINSTANCE _hInstance);
	BOOL InitInstance(HINSTANCE, int);

private:
	HINSTANCE hInstance;                                // ���� �ν��Ͻ��Դϴ�.
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	HICON hIcon;
	HICON hIconSmall;
	int cmdShow;
	MSG msg;
};

