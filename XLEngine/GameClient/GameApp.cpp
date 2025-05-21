#include <iostream>
#include "GameApp.h"
#include "Engine.h"

void GameApp::Initialize(HWND hWnd)
{
	currentFrameTime = std::chrono::steady_clock().now();
	previousFrameTime = std::chrono::steady_clock().now();

	engine.Initialize(hWnd);

	currentScene.Initialize(engine.GetRenderer(), engine.GetBuilder());
}

void GameApp::Update()
{
	engine.Update();

	currentScene.Update(deltaTime.count());
	currentScene.Render(deltaTime.count());
	
	currentFrameTime = std::chrono::steady_clock().now();
	deltaTime = currentFrameTime - previousFrameTime;
	std::cout << "DeltaTime: " << deltaTime.count();
	std::cout << "   FPS: " << 1.0f / deltaTime.count() << std::endl;

	previousFrameTime = std::chrono::steady_clock().now();
}

void GameApp::Finalize()
{
	engine.Finalize();

	currentScene.Finalize();
}