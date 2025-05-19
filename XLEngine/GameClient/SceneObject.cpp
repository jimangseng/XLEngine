#include "SceneObject.h"
#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"

SceneObject::SceneObject()
	:geometry{},
	material{},
	numIndices{}
{

}

void SceneObject::Initialize()
{

}

void SceneObject::Update()
{

}

void SceneObject::Render()
{

}

void SceneObject::Finalize()
{

}

void SceneObject::SetGeometry(std::unique_ptr<Geometry> _geometry)
{
	geometry = std::move(_geometry);
}

void SceneObject::SetMaterial(std::unique_ptr<Material> _material)
{
	material = std::move(_material);
}
