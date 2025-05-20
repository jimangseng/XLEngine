#pragma once

#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"
#include "SceneObject.h"
#include "Builder.h"

class Scene;

/*
* ������ ���� ���� ����.
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
	void Initialize(const D3D11Core& _core, const Builder& _builder);
	void Draw(Scene & _scene);
	void Finalize();

private:
	void ConfigurePipelineStates();
	void BindObjects(const std::unique_ptr<SceneObject>& _object);

private:
	const D3D11Core* core;
	const Builder* builder;

	// cached d3d resources - Core�� å�� �и��� ���� �����غ� ��. 25. 5. 17. jimangseng
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain1* swapChain;
	ID3D11RenderTargetView* backBufferView;
	HRESULT result;
	// com_ptr�� �ٲٱ�

	winrt::com_ptr<ID3D11Buffer> cbPerObject;

};