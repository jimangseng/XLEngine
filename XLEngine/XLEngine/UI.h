#pragma once

class D3D11Core;

class UI
{
public:
	static void Initialize(HWND _hWnd, const D3D11Core& _core);
	static void Finalize();

	static void BeginFrame();
	static void EndFrame();

	static void SetStyle();
	static void DrawDemo();
};