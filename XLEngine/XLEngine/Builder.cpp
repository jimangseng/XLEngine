#include "Builder.h"
#include "D3D11Core.h"
#include "Material.h"

void Builder::Initialize(D3D11Core& _core)
{
	core = &_core;
}

std::shared_ptr<Material> Builder::BuildMaterial(std::vector<D3D11_INPUT_ELEMENT_DESC> _layout) const
{
	ID3D11Device* device{ core->GetDevice() };
	HRESULT result{};

	// vertex shader
	winrt::com_ptr<ID3DBlob> vsBlob{};
	D3DReadFileToBlob(L"C:/XLEngine/XLEngine/Shader/VertexShader.cso", vsBlob.put());
	winrt::com_ptr<ID3D11VertexShader> vertexShader;
	result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader.put());

	// pixel shader
	winrt::com_ptr<ID3DBlob> psBlob{};
	D3DReadFileToBlob(L"C:/XLEngine/XLEngine/Shader/PixelShader.cso", psBlob.put());
	winrt::com_ptr<ID3D11PixelShader> pixelShader;
	result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, pixelShader.put());

	// input layout
	winrt::com_ptr<ID3D11InputLayout> inputLayout;
	result = device->CreateInputLayout(_layout.data(), 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), inputLayout.put());


	// make material struct
	auto mat = std::make_shared<Material>();

	mat->SetVSBlob(vsBlob);
	mat->SetPSBlob(psBlob);

	mat->SetVS(vertexShader);
	mat->SetPS(pixelShader);

	mat->SetInputLayout(inputLayout);

	return mat;

}