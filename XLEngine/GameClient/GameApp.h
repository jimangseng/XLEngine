#pragma once

#include "Engine.h"
#include "Scene.h"

/*
* 게임 클라이언트 어플리케이션 진입점.
* 25. 5. 15. jimangseng
*/
class GameApp
{
public:
	GameApp() = default;
	~GameApp() = default;
	GameApp(const GameApp&) = delete;
	GameApp& operator= (const GameApp&) = delete;

public:
	void Initialize(HWND hWnd);
	void Update();
	void Finalize();

private:
	Engine engine;
	Scene currentScene;
};