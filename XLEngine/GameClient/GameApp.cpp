#include "GameApp.h"
#include "../XLEngine/EngineApp.h"

void GameApp::Initialize(HWND hWnd)
{
	engine.Initialize(hWnd);
}

void GameApp::Update()
{
	engine.Update();
}

void GameApp::Finalize()
{
	engine.Finalize();
}
