#pragma once

#include "D3D11Common.h"

class Triangle
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 position{};
		DirectX::XMFLOAT4 color{};
	};

public:
	Triangle();
	~Triangle() = default;
	Triangle(const Triangle&) = delete;
	Triangle& operator= (const Triangle&) = delete;

public:
	const std::vector<Vertex>& GetVertices() { return vertices; }
	const std::vector<UINT32>& GetIndices() { return indices; }
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetLayout() { return layout; }

private:
	std::vector<Vertex> vertices;
	std::vector<UINT32> indices;
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
};

