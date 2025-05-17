#pragma once

#include "D3D11Core.h"

template <typename TVertex>
struct GeometryInfo
{
	std::vector<TVertex> vertices;
	std::vector<UINT32> indices;

	ID3DBlob* vsBlob;
	ID3DBlob* psBlob;

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout;
};

/*
* 지오메트리 (VB, IB, InputLayout) 관련
* 25. 5. 15. jimangseng
*/
class Geometry
{
public:
	Geometry() = default;
	~Geometry() = default;
	Geometry(const Geometry&) = default;	// todo: 복사생성자, 복사 대입 연산자 구현하기
	Geometry& operator= (const Geometry&) = default;

public:
	//bool Initialize(const D3D11Core& _core, const GeometryInfo& _info);
	bool Finalize();

private:
	const D3D11Core* core;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	HRESULT result;

public:
	template<typename TVertex>
	bool Initialize(const D3D11Core& _core, const GeometryInfo<TVertex>& _info)
	{
		core = &_core;

		device = _core.GetDevice();
		deviceContext = _core.GetDeviceContext();

		// Vertex & Vertex Buffer
		CD3D11_BUFFER_DESC VBDesc{};
		VBDesc.ByteWidth = static_cast<UINT> (sizeof(TVertex) * _info.vertices.size());
		VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA VBData{};
		VBData.pSysMem = _info.vertices.data();

		winrt::com_ptr<ID3D11Buffer> vertexBuffer{};
		device->CreateBuffer(&VBDesc, &VBData, vertexBuffer.put());

		UINT stride = sizeof(TVertex);
		UINT offset = 0;
		ID3D11Buffer* VBs[] = { vertexBuffer.get() };

		deviceContext->IASetVertexBuffers(0, 1, VBs, &stride, &offset); // 일단 버퍼 하나만 호환. 5. 16.



		// Index & Index Buffer

		CD3D11_BUFFER_DESC IBDesc{};
		IBDesc.ByteWidth = static_cast<UINT>(_info.indices.size() * sizeof(UINT32));
		IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		IBDesc.StructureByteStride = static_cast<UINT> (sizeof(UINT32));

		D3D11_SUBRESOURCE_DATA IBData
		{
			_info.indices.data(),
			0,
			0
		};

		winrt::com_ptr<ID3D11Buffer> indexBuffer{};

		result = device->CreateBuffer(&IBDesc, &IBData, indexBuffer.put());

		// InputLayout
		winrt::com_ptr<ID3D11InputLayout> inputLayout;
		device->CreateInputLayout(_info.inputLayout.data(), 2, _info.vsBlob->GetBufferPointer(), _info.vsBlob->GetBufferSize(), inputLayout.put());
		
		
		deviceContext->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetInputLayout(inputLayout.get());

		return true;
	}
};