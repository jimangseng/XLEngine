#include <vector>
#include "D3D11Common.h"
#include "Scene.h"
#include "Renderer.h"
#include "Geometry.h"
#include "PrimitiveFactory.h"
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

	// make primitive factory
	PrimitiveFactory primitiveFactory;

	// get primitives from factory
	auto triangle = primitiveFactory.CreatePrimitive(Primitives::Triangle);
	auto quad = primitiveFactory.CreatePrimitive(Primitives::Quad);
	auto cube = primitiveFactory.CreatePrimitive(Primitives::Cube);

	// build geometry and material
	auto geometryTri{ builder->BuildGeometry(triangle->GetVertices(), triangle->GetIndices()) };
	auto materialTri{ builder->BuildMaterial(triangle->GetLayout()) };

	auto geometryQuad{ builder->BuildGeometry(quad->GetVertices(), quad->GetIndices()) };
	auto materialQuad{ builder->BuildMaterial(quad->GetLayout()) };

	auto geometryCube{ builder->BuildGeometry(cube->GetVertices(), cube->GetIndices()) };

	// make 10 cubes
	for (int i = 0; i < 10; ++i)
	{
		auto obj = std::make_unique<SceneObject>();

		obj->SetGeometry(geometryCube);
		obj->SetMaterial(materialQuad);
		obj->Scale(0.1f);
		obj->SetPosition(Math::Vector3{(i % 5)* 0.2f - 0.4f , ((i/5)-0.5f)*(-0.5f) , 0.0f});

		objects.push_back(std::move(obj));
	}
}
	
void Scene::Update()
{
	// rotate 10 cubes
	for (auto& object : objects)
	{
		object->Pitch(0.02f);
		object->Yaw(0.02f);
	}
}

void Scene::Render()
{
	renderer->Draw(*this);
}

void Scene::Finalize()
{
}
