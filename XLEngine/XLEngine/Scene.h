#pragma once

#include "Geometry.h"
#include "Material.h"
#include <memory>

/*
* ��
* 25. 5. 17. jimangseng
*/
class Scene
{
public:
	Scene();
	~Scene() = default;
	Scene(const Scene&) = delete;	// ���� ���� �����ؾ� �ϴ°�? 25. 5. 17.
	Scene& operator= (const Scene&) = delete;

public:
	void Initialize(const D3D11Core * _core);
	void Update();
	void Finalize();

public:
	size_t GetNumIndices() const { return numIndices; }

private:
	std::unique_ptr<Geometry> testGeometry;
	std::unique_ptr<Material> testMaterial;

	size_t numIndices;
};