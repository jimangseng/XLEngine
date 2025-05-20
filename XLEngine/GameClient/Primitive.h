#pragma once

#include <vector>
#include "D3D11Common.h"

class Primitive
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 position{};
		DirectX::XMFLOAT4 color{};
	};

public:
	Primitive() = default;
	~Primitive() = default;
	Primitive(const Primitive&) = delete;
	Primitive& operator= (const Primitive&) = delete;

public:
	const std::vector<Vertex>& GetVertices() { return vertices; }
	const std::vector<UINT32>& GetIndices() { return indices; }
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetLayout() { return layout; }

	void SetVertices(const std::vector<Vertex>& _vertices) { vertices = _vertices; }
	void SetIndices(const std::vector<UINT32>& _indices) { indices = _indices; }
	void SetLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& _layout) { layout = _layout; }

private:
	std::vector<Vertex> vertices;
	std::vector<UINT32> indices;
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
};

