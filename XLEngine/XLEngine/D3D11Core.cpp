#include "D3D11Core.h"

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "UI.h"

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
		DXGI_FORMAT_R8G8B8A8_UNORM,
		false,
		{1, 0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_NONE,
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

	tDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	// create RTV
	result = device->CreateRenderTargetView(backBuffer.get(), nullptr, backBufferView.put());

	/// For IMGUI Viewport
	result = device->CreateTexture2D(&tDesc, nullptr, IMGUIViewportTexture.put());
	result = device->CreateRenderTargetView(IMGUIViewportTexture.get(), nullptr, IMGUIViewportRTV.put());
	result = device->CreateShaderResourceView(IMGUIViewportTexture.get(), nullptr, IMGUIViewportSRV.put());
}

void D3D11Core::BeginFrame() const
{
	UI::BeginFrame();

	// IMGUI의 Scene Viewport에 렌더
	ID3D11RenderTargetView* viewportRTV = IMGUIViewportRTV.get();
	deviceContext->OMSetRenderTargets(1, &viewportRTV, nullptr);
	deviceContext->ClearRenderTargetView(viewportRTV, backgroundColor);
}

void D3D11Core::EndFrame() const
{
	// 백버퍼에 더미 렌더
	ID3D11RenderTargetView* backBufferRTV = backBufferView.get();

	if (backBufferRTV == nullptr)
		return;

	deviceContext->OMSetRenderTargets(1, &backBufferRTV, nullptr);
	deviceContext->ClearRenderTargetView(backBufferRTV, backgroundColor);


	UI::EndFrame();

	// present
	swapChain->Present(1, 0);
}

void D3D11Core::Finalize() const
{
}

void D3D11Core::ResizeRenderTarget(float _width, float _height)
{
	if (_width == 0 || _height == 0)
		return;

	// 기존 바인딩 해제
	deviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	// 기존 백버퍼 뷰 해제
	backBufferView = nullptr;
	backBuffer = nullptr;

	// 스왑체인 리사이즈
	HRESULT hr = swapChain->ResizeBuffers(0, static_cast<float>(_width), static_cast<float>(_height), DXGI_FORMAT_UNKNOWN, 0);
	if (FAILED(hr)) return;

	// 새로운 백버퍼 가져오기
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), backBuffer.put_void());

	// 새로운 RTV 생성
	hr = device->CreateRenderTargetView(backBuffer.get(), nullptr, backBufferView.put());
	if (FAILED(hr)) return;
}
