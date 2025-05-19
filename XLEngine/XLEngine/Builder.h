#pragma once

#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"

/*
* Geometry와 Material 객체를 생성해주는 엔진 요소
* 오직 생성만 하고, 바인드는 renderer가 한다.
* 25. 5. 19. jimangseng
*/
class Builder
{
public:
	Builder() = default;
	~Builder() = default;
	Builder(const Builder&) = delete;
	Builder& operator= (const Builder&) = delete;

public:
	void Initialize(D3D11Core& _core);

public:
	std::shared_ptr<Material> BuildMaterial(std::vector<D3D11_INPUT_ELEMENT_DESC>) const;
	
	template <typename TVertex>
	std::shared_ptr<Geometry> BuildGeometry(const std::vector<TVertex>& _vertices, const std::vector<UINT32>& _indices) const
	{
		ID3D11Device* device{ core->GetDevice() };
		HRESULT result{};

		// create vertex buffer
		CD3D11_BUFFER_DESC VBDesc{};
		VBDesc.ByteWidth = static_cast<UINT> (sizeof(TVertex) * _vertices.size());
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
		auto geometry = std::make_shared<Geometry>();

		geometry->SetStride(sizeof(TVertex));
		geometry->SetOffset(0);

		geometry->SetVB(vertexBuffer);
		geometry->SetIB(indexBuffer);

		geometry->SetNumIndices(_indices.size());

		return geometry;
	}

private:
	D3D11Core* core;
};