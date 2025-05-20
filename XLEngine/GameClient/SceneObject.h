#pragma once

#include "Geometry.h"
#include "Transform.h"
#include "Primitive.h"

class D3D11Core;
class Material;

/*
* 씬에 배치되는 오브젝트
* 25. 5. 17. jimangseng
*/
class SceneObject
{
public:
	SceneObject();
	~SceneObject() = default;
	SceneObject(const SceneObject&) = default;
	SceneObject& operator= (const SceneObject&) = default;

public:
	void Initialize();
	void Update();
	void Render();
	void Finalize();

public:
	void SetGeometry(std::shared_ptr<Geometry> _geometry);
	void SetMaterial(std::shared_ptr<Material> _material);
	void SetPrimitive(std::shared_ptr<Primitive> _primitive) { primitive = _primitive; }

	// Transform 관련
	void SetPosition(Math::Vector3 _position) { transform.position = _position; }
	void Roll(float _y) { transform.rotation.z += _y; }
	void Pitch(float _x) { transform.rotation.x += _x; }
	void Yaw(float _z) { transform.rotation.y += _z; }
	void Scale(float _scale)
	{	transform.scale.x *= _scale;
		transform.scale.y *= _scale;
		transform.scale.z *= _scale;
	}

public:
	size_t GetNumIndices() const { return geometry->GetNumIndices(); }
	const std::shared_ptr<Geometry>& GetGeometry() { return geometry; }
	const std::shared_ptr<Material>& GetMaterial() { return material; }
	const std::shared_ptr<Primitive>& GetPrimitive() { return primitive; }
	Transform GetTransform() { return transform; }

private:
	Transform transform;
	std::shared_ptr<Geometry> geometry;
	std::shared_ptr<Material> material;

	size_t numIndices;

	std::shared_ptr<Primitive> primitive;
};

