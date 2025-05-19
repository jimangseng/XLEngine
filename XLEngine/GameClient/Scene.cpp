#include <vector>
#include "D3D11Common.h"
#include "Scene.h"
#include "Renderer.h"
#include "Geometry.h"

Scene::Scene()
	: renderer{ },
	builder{},
	objects{ }
{
}

void Scene::Initialize(Renderer& _renderer, Builder& _builder)
{
	// receivce renderer pointer to member
	renderer = &_renderer;
	builder = &_builder;

	// Primitive로 데이터 구조 정의
	std::vector<Geometry::Vertex> vertices
	{
		{ { 0.0f, 0.5f, 0.1f }, { 1.f, 0.f, 0.f, 1.f } },
		{ { 0.5f, -0.5f, 0.1f }, { 0.f, 1.f, 0.f, 1.f } },
		{ { -0.5f, -0.5f, 0.1f }, { 0.f, 0.f, 1.f, 1.f } }
	};

	std::vector<UINT32> indices { 0, 1, 2 };

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Geometry::Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Geometry::Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// Builder를 통해 Geometry와 Material 생성 -> Vertex 구조, Inputlayout에 대한 고민 25. 5. 19. jimangseng
	auto geometry{ builder->BuildGeometry(vertices, indices) };
	auto material{ builder->BuildMaterial(layout) };

	// 만들어진 Geometry와 Material을 오브젝트에 연결하고 오브젝트 목록(씬 그래프)에 넣는다.
	auto object{ std::make_unique<SceneObject>() };
	object->Initialize();
	object->SetGeometry(std::move(geometry));
	object->SetMaterial(std::move(material));

	objects.push_back(std::move(object));
}
	
void Scene::Update()
{

}

void Scene::Render()
{
	renderer->Draw(*this);
}

void Scene::Finalize()
{
}
