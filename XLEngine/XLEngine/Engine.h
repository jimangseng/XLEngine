#pragma once

#include "D3D11Core.h"
#include "Builder.h"
#include "Renderer.h"

/*
* 그래픽스 엔진 진입점.
* 25. 5. 15. jimangseng
*/

class Engine
{
public:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine&) = delete;
	Engine& operator= (const Engine&) = delete;

public:
	void Initialize(HWND hWnd);
	void Update();
	void Finalize();

public:
	Builder& GetBuilder() const { return *builder.get(); }
	Renderer& GetRenderer() const { return *renderer.get(); }

private:
	std::shared_ptr<D3D11Core> core;
	std::shared_ptr<Builder> builder;
	std::shared_ptr<Renderer> renderer;
};