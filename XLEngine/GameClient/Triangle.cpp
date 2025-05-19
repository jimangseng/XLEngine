#include "Triangle.h"
#include "SceneObject.h"

Triangle::Triangle()
{
	vertices = 
	{
		{ { 0.0f, 0.5f, 0.1f }, { 1.f, 0.f, 0.f, 1.f } },
		{ { 0.5f, -0.5f, 0.1f }, { 0.f, 1.f, 0.f, 1.f } },
		{ { -0.5f, -0.5f, 0.1f }, { 0.f, 0.f, 1.f, 1.f } }
	};

	indices = { 0, 1, 2 };

	layout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
}