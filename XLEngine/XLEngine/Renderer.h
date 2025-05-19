#pragma once

#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"
#include "SceneObject.h"

class Scene;

/*
* 렌더링 관련 로직 수행.
* 25. 5. 15. jimangseng
*/
class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

public:
	void Initialize(D3D11Core& _core);
	void Draw(Scene & _scene);
	void Finalize();

private:
	void ConfigurePipelineStates();
	void BindObjects(const std::unique_ptr<SceneObject>& _object);

private:
	D3D11Core* core;

	// cached d3d resources - Core의 책임 분리에 대해 생각해볼 것. 25. 5. 17. jimangseng
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain1* swapChain;
	ID3D11RenderTargetView* backBufferView;
	HRESULT result;

};