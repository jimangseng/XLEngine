#pragma once

#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"
#include "Scene.h"

/*
* 렌더링 관련 로직 수행.
* 25. 5. 15. jimangseng
*/
class Renderer
{
public:
	Renderer();
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

public:
	void Initialize(HWND hWnd);
	void Update();
	void Finalize();

private:
	void ConfigurePipelineStates();

private:
	std::unique_ptr<D3D11Core> core;

	// d3d resources
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain1* swapChain;
	ID3D11RenderTargetView* backBufferView;
	HRESULT result;

	// for test
	std::unique_ptr<Scene> testScene;

};