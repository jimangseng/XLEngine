#include <iostream>
#include "GameApp.h"
#include "Engine.h"
#include "InputManager.h"
#include "DebugLog.h"

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
	
	// Scene
	currentScene.Update(deltaTime.count());
	currentScene.Render(deltaTime.count());

	// Input
	InputManager::Update();

	// Timer
	currentFrameTime = std::chrono::steady_clock().now();
	deltaTime = currentFrameTime - previousFrameTime;
	
	DebugLog::Add("DeltaTime: " + std::to_string(deltaTime.count()) + '\n');
	DebugLog::Add("FPS: " + std::to_string(1.0f / deltaTime.count()) + '\n');

	previousFrameTime = std::chrono::steady_clock().now();
}

void GameApp::Finalize()
{
	engine.Finalize();

	currentScene.Finalize();
}