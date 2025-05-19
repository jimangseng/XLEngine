#include "Engine.h"

void Engine::Initialize(HWND hWnd)
{
	core = std::make_shared<D3D11Core>();
	core->Initialize(hWnd);

	builder = std::make_shared<Builder>();
	builder->Initialize(*core);

	renderer = std::make_shared<Renderer>();
	renderer->Initialize(*core);
}

void Engine::Update()
{

}

void Engine::Finalize()
{
	renderer->Finalize();
}