#pragma once

#include "Renderer.h"
#include "Builder.h"
#include "SceneObject.h"
#include "Geometry.h"
#include "Material.h"
#include <memory>

class Renderer;

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
	void Initialize(Renderer& _renderer, Builder& _builder);
	void Update(float _deltaTime);
	void Render(float _deltaTime);
	void Finalize();

public:
	const std::vector<std::unique_ptr<SceneObject>>& GetObjects() const { return objects; }

private:
	// �������� ������ ������ - ������ ����
	Renderer* renderer;
	Builder* builder;

	// ������Ʈ ��� - ���� �� �׷����� ���� ����
	std::vector<std::unique_ptr<SceneObject>> objects;	// ������ ���� ��� 25. 5. 17.

};