#pragma once

#include "D3D11Common.h"
#include "Primitive.h"

enum class Primitives
{
	Triangle,
	Quad,
	Cube
};

class PrimitiveFactory
{
public:
	PrimitiveFactory() = default;
	~PrimitiveFactory() = default;
	PrimitiveFactory(const PrimitiveFactory&) = delete;
	PrimitiveFactory& operator= (const PrimitiveFactory&) = delete;

public:
	const std::shared_ptr<Primitive>& CreatePrimitive(Primitives _primitive);

private:
	std::shared_ptr<Primitive> primitive;

private:
	std::vector<Primitive::Vertex> vertices;
	std::vector<UINT32> indices;
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
};

