#include "D3D11Core.h"

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

void D3D11Core::Initialize(const HWND _hWnd)
{
	hWnd =_hWnd;

	// create factory
	result = CreateDXGIFactory1(__uuidof(IDXGIFactory2), factory.put_void());

	// enumerate adapter
	result = factory->EnumAdapters1(0, adapter.put());

	// create device
	result = D3D11CreateDevice
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		device.put(),
		nullptr,
		deviceContext.put()
	);

	// swap chain description
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc =
	{
		0,
		0,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		false,
		{1, 0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_IGNORE,
		0
	};

	// create swap chain
	result = factory->CreateSwapChainForHwnd
	(
		device.get(),
		hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		swapChain.put()
	);

	// get render target from swap chain
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), backBuffer.put_void());

	D3D11_TEXTURE2D_DESC tDesc;
	backBuffer->GetDesc(&tDesc);

	screenSize.width = static_cast<float>(tDesc.Width);
	screenSize.height = static_cast<float>(tDesc.Height);

	// create RTV
	result = device->CreateRenderTargetView
	(
		backBuffer.get(),
		NULL,
		backBufferView.put()
	);

}

void D3D11Core::BeginFrame()
{
	ID3D11RenderTargetView* rtvs[]{ backBufferView.get()};
	deviceContext->OMSetRenderTargets(1, rtvs, NULL);

	float backgroundColor[4]{ 0.05f, 0.05f, 0.05f, 1.0f };
	deviceContext->ClearRenderTargetView(backBufferView.get(), backgroundColor);
}

void D3D11Core::EndFrame()
{
	swapChain->Present1(0, 0, &presentParams);
}

void D3D11Core::Finalize()
{
}