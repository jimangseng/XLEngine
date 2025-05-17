#pragma once

#include "Renderer.h"

class D3D11Core;

/*
* �׷��Ƚ� ���� ������.
* 25. 5. 15. jimangseng
*/

class EngineApp
{
public:
	EngineApp() = default;
	~EngineApp() = default;
	EngineApp(const EngineApp&) = delete;
	EngineApp& operator= (const EngineApp&) = delete;

public:
	void Initialize(HWND hWnd);
	void Update();
	void Finalize();

private:
	Renderer renderer;
};