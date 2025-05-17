#include "EngineApp.h"

void EngineApp::Initialize(HWND hWnd)
{
	renderer.Initialize(hWnd);
}

void EngineApp::Update()
{
	renderer.Update();
}

void EngineApp::Finalize()
{
	renderer.Finalize();
}