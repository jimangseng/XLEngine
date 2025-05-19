#include "Builder.h"
#include "D3D11Core.h"
#include "Material.h"

void Builder::Initialize(D3D11Core& _core)
{
	core = &_core;
}

std::unique_ptr<Geometry> Builder::BuildGeometry(const std::vector<Geometry::Vertex>& _vertices, const std::vector<UINT32>& _indices) const
{
	ID3D11Device* device{ core->GetDevice() };
	HRESULT result{};

	// create vertex buffer
	CD3D11_BUFFER_DESC VBDesc{};
	VBDesc.ByteWidth = static_cast<UINT> (sizeof(Geometry::Vertex) * _vertices.size());
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA VBData{};
	VBData.pSysMem = _vertices.data();

	winrt::com_ptr<ID3D11Buffer> vertexBuffer{};
	result = device->CreateBuffer(&VBDesc, &VBData, vertexBuffer.put());

	// create index buffer
	CD3D11_BUFFER_DESC IBDesc{};
	IBDesc.ByteWidth = static_cast<UINT>(_indices.size() * sizeof(UINT32));
	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBDesc.StructureByteStride = static_cast<UINT> (sizeof(UINT32));

	D3D11_SUBRESOURCE_DATA IBData
	{
		_indices.data(),
		0,
		0
	};

	winrt::com_ptr<ID3D11Buffer> indexBuffer{};
	result = device->CreateBuffer(&IBDesc, &IBData, indexBuffer.put());


	// make geometry struct
	auto geometry = std::make_unique<Geometry>();

	geometry->SetStride(sizeof(Geometry::Vertex));
	geometry->SetOffset(0);

	geometry->SetVB(vertexBuffer);
	geometry->SetIB(indexBuffer);

	geometry->SetNumIndices(_indices.size());

	return geometry;
}

std::unique_ptr<Material> Builder::BuildMaterial(std::vector<D3D11_INPUT_ELEMENT_DESC> _layout) const
{
	ID3D11Device* device{ core->GetDevice() };
	HRESULT result{};

	// vertex shader
	winrt::com_ptr<ID3DBlob> vsBlob{};
	D3DReadFileToBlob(L"../x64/Debug/VertexShader.cso", vsBlob.put());
	winrt::com_ptr<ID3D11VertexShader> vertexShader;
	result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader.put());

	// pixel shader
	winrt::com_ptr<ID3DBlob> psBlob{};
	D3DReadFileToBlob(L"../x64/Debug/PixelShader.cso", psBlob.put());
	winrt::com_ptr<ID3D11PixelShader> pixelShader;
	result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, pixelShader.put());

	// input layout
	winrt::com_ptr<ID3D11InputLayout> inputLayout;
	result = device->CreateInputLayout(_layout.data(), 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), inputLayout.put());


	// make material struct
	auto mat = std::make_unique<Material>();

	mat->SetVSBlob(vsBlob);
	mat->SetPSBlob(psBlob);

	mat->SetVS(vertexShader);
	mat->SetPS(pixelShader);

	mat->SetInputLayout(inputLayout);

	return mat;

}
