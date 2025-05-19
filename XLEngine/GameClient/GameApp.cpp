#include "GameApp.h"
#include "Engine.h"

void GameApp::Initialize(HWND hWnd)
{
	engine.Initialize(hWnd);

	currentScene.Initialize(engine.GetRenderer(), engine.GetBuilder());
}

void GameApp::Update()
{
	engine.Update();

	currentScene.Update();
	currentScene.Render();
}

void GameApp::Finalize()
{
	engine.Finalize();

	currentScene.Finalize();
}