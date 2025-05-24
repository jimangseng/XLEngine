#include "framework.h"
#include "GameApp.h"

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_win32.h"
#include "../imgui/backends/imgui_impl_dx11.h"

/*
* Windows 어플리케이션 진입점.
* 25. 5. 15. jimangseng
*/

HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	ImGui_ImplWin32_EnableDpiAwareness();

	HWND hWnd = InitializeWindow(hInstance, nCmdShow);
	MSG msg;

	// GameApp 인스턴스 생성
	GameApp gameApp{};

	// GameApp Initialize
	gameApp.Initialize(hWnd);

	// Game Loop
	while (true)
	{
		// Process Window Message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		// GameApp Update
		gameApp.Update();
	}

	// GameApp Finalize
	gameApp.Finalize();

	return (int)msg.wParam;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// IMGUI hook
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return (LRESULT)1;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("XLEngine");
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	HWND hWnd = CreateWindowW(TEXT("XLEngine"), TEXT("XLEngine"), WS_OVERLAPPEDWINDOW,
		100, 100, 1280, 720, nullptr, nullptr, hInstance, nullptr);

	//ShowWindow(hWnd, SW_HIDE);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

