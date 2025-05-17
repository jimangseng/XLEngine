#pragma once

#include "../XLEngine/EngineApp.h"

/*
* ���� Ŭ���̾�Ʈ ���ø����̼� ������.
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
	EngineApp engine;
};