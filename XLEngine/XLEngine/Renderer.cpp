#include "Renderer.h"

#include <memory>

#include "Scene.h"
#include "Geometry.h"
#include "Material.h"
#include "SceneObject.h"

#include "UI.h"
#include "D3D11Common.h"

#include "DebugLog.h"

void Renderer::Initialize(D3D11Core& _core, Builder& _builder)
{
	this->core = &_core;	// todo 25. 5. 23.

	// cache d3d resources
	device = core->GetDevice();
	deviceContext = core->GetDeviceContext();

	// build and bind Constant Buffer
	cbPerObject = _builder.BuildConsantBuffer();
	ID3D11Buffer* CBs[]{ cbPerObject.get() };
	deviceContext->VSSetConstantBuffers(0, 1, CBs);

	ConfigurePipelineStates();
}

void Renderer::Draw(Scene & _scene)
{
	core->BeginFrame();

	// update and draw objects
	for (auto& object : _scene.GetObjects())	// SceneObject의 소유권 문제에 대해 생각해보기 // 25. 5. 24.
	{
		Math::Matrix data = object->GetTransform().GetWVPMatrix();

		D3D11_MAPPED_SUBRESOURCE mappedResource{};
		deviceContext->Map(cbPerObject.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, &data, sizeof(Math::Matrix));
		deviceContext->Unmap(cbPerObject.get(), 0);

		BindObjects(object);
		deviceContext->DrawIndexed(static_cast<UINT>(object->GetNumIndices()), 0, 0);
	}

	// draw UI
	UI::DrawDockSpace(*core);
	UI::DrawSceneViewport(*core);
	UI::DrawInspector();
	UI::DrawDemo();

	// render Debug Log Panel
	DebugLog::DrawPanel();

	core->EndFrame();
}

void Renderer::Finalize()
{
	core->Finalize();
}

void Renderer::ConfigurePipelineStates()
{
	// Primitive Topology
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Rasterizer State
	CD3D11_RASTERIZER_DESC rasterDesc{ D3D11_DEFAULT };
	rasterDesc.DepthClipEnable = false;

	winrt::com_ptr<ID3D11RasterizerState> rasterizerState{}; // Material에 들어가야 하나?
	HRESULT result = device->CreateRasterizerState(&rasterDesc, rasterizerState.put());
	deviceContext->RSSetState(rasterizerState.get());

	// Viewport
	D3D11_VIEWPORT viewport { 0, 0, core->GetScreenSize().width, core->GetScreenSize().height, 0, 1};
	deviceContext->RSSetViewports(1, &viewport);

	//winrt::com_ptr<ID3D11Texture2D> depthStencilBuffer;
	//winrt::com_ptr<ID3D11DepthStencilView> depthStencilView;
	//winrt::com_ptr<ID3D11DepthStencilState> depthStencilState;
	//winrt::com_ptr<ID3D11ShaderResourceView> shaderResourceView;
	//winrt::com_ptr<ID3D11BlendState> blendState;
	//winrt::com_ptr<ID3D11SamplerState> samplerState;
	//deviceContext->OMSetDepthStencilState(depthStencilState.get(), 0);
	//deviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);
}

void Renderer::BindObjects(const std::unique_ptr<SceneObject>& _object)
{
	// bind material
	const auto& material = _object->GetMaterial();

	deviceContext->IASetInputLayout(material->GetInputLayout());
	deviceContext->VSSetShader(material->GetVS(), nullptr, 0);
	deviceContext->PSSetShader(material->GetPS(), nullptr, 0);


	// bind geometry
	const auto& geometry = _object->GetGeometry();

	ID3D11Buffer* vb = geometry->GetVB();
	ID3D11Buffer* ib = geometry->GetIB();

	deviceContext->IASetVertexBuffers(0, 1, &vb, &geometry->GetStride(), &geometry->GetOffset());
	deviceContext->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
}
