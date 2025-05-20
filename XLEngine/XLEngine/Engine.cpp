#include "Engine.h"

void Engine::Initialize(HWND hWnd)
{
	core = std::make_unique<D3D11Core>();
	core->Initialize(hWnd);

	builder = std::make_unique<Builder>();
	builder->Initialize(*core);

	renderer = std::make_unique<Renderer>();
	renderer->Initialize(*core, *builder); // todo unique_ptr 전달로 수정할 것 25. 5. 20.
}

void Engine::Update()
{

}

void Engine::Finalize()
{
	renderer->Finalize();
}