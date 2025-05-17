#include <vector>
#include "D3D11Common.h"
#include "Scene.h"

Scene::Scene()
	: testGeometry{std::make_unique<Geometry> ()},
	testMaterial{std::make_unique<Material> ()},
	numIndices{ 0 }
{
}

void Scene::Initialize(const D3D11Core* _core)
{
	///
	// Material
	testMaterial->Initialize(*_core, L"../x64/Debug/VertexShader.cso", L"../x64/Debug/PixelShader.cso");

	// Geometry
	struct Vertex
	{
		DirectX::XMFLOAT3 position{};
		DirectX::XMFLOAT4 color{};
	};

	std::vector<Vertex> vertices =
	{
		{ { 0.0f, 0.5f, 0.1f }, { 1.f, 0.f, 0.f, 1.f } },
		{ { 0.5f, -0.5f, 0.1f }, { 0.f, 1.f, 0.f, 1.f } },
		{ { -0.5f, -0.5f, 0.1f }, { 0.f, 0.f, 1.f, 1.f } }
	};

	std::vector<UINT32> indices = { 0, 1, 2 };
	numIndices = indices.size();

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	GeometryInfo<Vertex> tempGeoInfo;

	tempGeoInfo.vertices = std::move(vertices);       // 정점 데이터
	tempGeoInfo.indices = std::move(indices);

	tempGeoInfo.vsBlob = testMaterial->GetVSBlob();
	tempGeoInfo.psBlob = testMaterial->GetPSBlob();

	tempGeoInfo.inputLayout = layout;

	testGeometry->Initialize(*_core, tempGeoInfo);
}

void Scene::Update()
{
}

void Scene::Finalize()
{
}
