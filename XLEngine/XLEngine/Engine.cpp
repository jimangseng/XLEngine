#include "Engine.h"
#include "UI.h"

void Engine::Initialize(HWND hWnd)	
{
	core = std::make_unique<D3D11Core>();
	core->Initialize(hWnd);

	builder = std::make_unique<Builder>();
	builder->Initialize(*core);

	renderer = std::make_unique<Renderer>();
	renderer->Initialize(*core, *builder);
	UI::Initialize(hWnd, *core);
}

void Engine::Update()
{



}

void Engine::Finalize()
{
	core->Finalize();
	//builder->Finalize();
	renderer->Finalize();
	UI::Finalize();
}