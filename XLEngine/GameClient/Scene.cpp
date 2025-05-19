#include <vector>
#include "D3D11Common.h"
#include "Scene.h"
#include "Renderer.h"
#include "Geometry.h"
#include "Triangle.h"
#include "Transform.h"

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

	// triangle object
	auto triangle = std::make_shared<Triangle>();

	// build geometry and material
	auto geometry{ builder->BuildGeometry(triangle->GetVertices(), triangle->GetIndices()) };
	auto material{ builder->BuildMaterial(triangle->GetLayout()) };

	// set first object
	auto obj1 = std::make_unique<SceneObject>();
	obj1->SetGeometry(geometry);
	obj1->SetMaterial(material);

	auto obj2 = std::make_unique<SceneObject>();
	obj2->SetGeometry(geometry);
	obj2->SetMaterial(material);
	obj2->SetPosition(Math::Vector3{ 0.2f, 0.0f, 0.0f });

	// add object to vector
	objects.push_back(std::move(obj1));
	objects.push_back(std::move(obj2));
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
