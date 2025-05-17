#include "Renderer.h"
#include <vector>

Renderer::Renderer()
	: core { std::make_unique<D3D11Core>() },
	testScene{ std::make_unique<Scene>() }
{

}

void Renderer::Initialize(HWND hWnd)
{
	// initialize core
	core->Initialize(hWnd);

	// cache d3d resources
	device = core->GetDevice();
	deviceContext = core->GetDeviceContext();
	swapChain = core->GetSwapChain();
	backBufferView = core->GetBackBufferVew();

	// intialize scene
	testScene->Initialize(core.get());
	
	ConfigurePipelineStates();
}

void Renderer::Update()
{
	// bind and clear backbuffer
	core->BeginFrame();

	// draw
	deviceContext->DrawIndexed(testScene->GetNumIndices(), 0, 0);	// 씬에 다수의 오브젝트가 있다면? 25. 5. 17.

	// present
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
	result = device->CreateRasterizerState(&rasterDesc, rasterizerState.put());
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