#include "SceneObject.h"
#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"

SceneObject::SceneObject()
	:geometry{},
	material{},
	numIndices{},
	primitive{}
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

void SceneObject::SetGeometry(std::shared_ptr<Geometry> _geometry)
{
	geometry = _geometry;
}

void SceneObject::SetMaterial(std::shared_ptr<Material> _material)
{
	material = _material;
}
