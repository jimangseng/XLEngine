#include "D3D11Common.h"
#include "D3D11Core.h"

#include "Material.h"

bool Material::Initialize(const D3D11Core& _core, const WCHAR* _vsBlobPath, const WCHAR* _psBlobPath)
{
	ID3D11Device* device{ _core.GetDevice() };
	ID3D11DeviceContext* deviceContext{ _core.GetDeviceContext() };
	HRESULT result{};

	// Shader
	D3DReadFileToBlob(_vsBlobPath, vsBlob.put());

	winrt::com_ptr<ID3D11VertexShader> vertexShader;
	device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader.put());

	D3DReadFileToBlob(_psBlobPath, psBlob.put());

	winrt::com_ptr<ID3D11PixelShader> pixelShader;
	device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, pixelShader.put());

	// Bind
	deviceContext->VSSetShader(vertexShader.get(), nullptr, 0);
	deviceContext->PSSetShader(pixelShader.get(), nullptr, 0);

	return true;
}

bool Material::Finalize()
{
	return false;
}