#pragma once

#include <windows.h>
#include "D3D11Core.h"

/*
* UI 관련 (창 생성, IMGUI 셋팅 등)
* 25. 5. 21. jimangseng
*/
class UI
{
public:
	static void Initialize(HWND _hWnd, const D3D11Core& _core);
	static void Finalize();

	static void BeginFrame();
	static void EndFrame();

	static void SetStyle();

	static void DrawDemo();
	static void DrawDockSpace(D3D11Core& _core);
	static void DrawSceneViewport(const D3D11Core& _core);
	static void DrawInspector();

private:
	static const D3D11Core& core;
};