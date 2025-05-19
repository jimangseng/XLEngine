#pragma once

#include "Geometry.h"

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
	void SetGeometry(std::unique_ptr<Geometry> _geometry);
	void SetMaterial(std::unique_ptr<Material> _material);

public:
	size_t GetNumIndices() const { return geometry->GetNumIndices(); }
	const std::unique_ptr<Geometry>& GetGeometry() { return geometry; }
	const std::unique_ptr<Material>& GetMaterial() { return material; }

private:
	// Transform transform;		// 25. 5. 19. 추가 예정
	std::unique_ptr<Geometry> geometry;
	std::unique_ptr<Material> material;

	size_t numIndices;
};

