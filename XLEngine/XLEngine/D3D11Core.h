#pragma once

#include "D3D11Common.h"

struct ScreenSize
{
	float width;
	float height;
};

/*
* D3D11 자원 (디바이스, 디바이스 컨텍스트, 스왑체인) 초기화 및 보관.
* TestDefaultScene() -> 임시 초기화
* 25. 05. 15. jimangseng
*/
class D3D11Core
{
public:
	D3D11Core() = default;
	~D3D11Core() = default;
	D3D11Core(const D3D11Core&) = delete;
	D3D11Core& operator= (const D3D11Core&) = delete;

public:
	void Initialize(const HWND _hWnd);
	void BeginFrame() const;
	void EndFrame() const;
	void Finalize() const;

public:
	ID3D11Device* GetDevice() const { return device.get(); }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext.get(); }
	IDXGISwapChain1* GetSwapChain() const { return swapChain.get(); }
	ID3D11Texture2D* GetBackBuffer() const { return backBuffer.get(); }
	ID3D11RenderTargetView* GetBackBufferVew() const { return backBufferView.get(); }
	ID3D11ShaderResourceView* GetBackBufferSRV() const { return backBufferSRV.get(); }
	ScreenSize GetScreenSize() const { return screenSize; }
	HWND GetWindowHandle() const { return hWnd; }

	ID3D11RenderTargetView* GetViewportRTV() const { return IMGUIViewportRTV.get(); }
	ID3D11ShaderResourceView* GetViewportSRV() const { return IMGUIViewportSRV.get(); }

private:
	// D3D 자원들
	winrt::com_ptr<ID3D11Device> device;
	winrt::com_ptr<ID3D11DeviceContext> deviceContext;

	winrt::com_ptr<IDXGIFactory2> factory;
	winrt::com_ptr<IDXGIAdapter1> adapter;
	winrt::com_ptr<IDXGISwapChain1> swapChain;

	winrt::com_ptr<ID3D11Texture2D> backBuffer;
	winrt::com_ptr<ID3D11RenderTargetView> backBufferView;
	winrt::com_ptr<ID3D11ShaderResourceView> backBufferSRV;

	// misc
	DXGI_PRESENT_PARAMETERS presentParams;
	HRESULT result;
	ScreenSize screenSize;
	HWND hWnd;	// window handle


	/// For IMGUI Viewport
	winrt::com_ptr<ID3D11Texture2D> IMGUIViewportTexture;
	winrt::com_ptr<ID3D11RenderTargetView> IMGUIViewportRTV;
	winrt::com_ptr<ID3D11ShaderResourceView> IMGUIViewportSRV;

	float backgroundColor[4]{ 0.05f, 0.05f, 0.05f, 1.0f };
};