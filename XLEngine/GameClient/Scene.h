#pragma once

#include "Renderer.h"
#include "Builder.h"
#include "SceneObject.h"
#include "Geometry.h"
#include "Material.h"
#include <memory>

class Renderer;

/*
* 씬
* 25. 5. 17. jimangseng
*/
class Scene
{
public:
	Scene();
	~Scene() = default;
	Scene(const Scene&) = delete;	// 씬은 복사 가능해야 하는가? 25. 5. 17.
	Scene& operator= (const Scene&) = delete;

public:
	void Initialize(Renderer& _renderer, Builder& _builder);
	void Update(float _deltaTime);
	void Render(float _deltaTime);
	void Finalize();

public:
	const std::vector<std::unique_ptr<SceneObject>>& GetObjects() const { return objects; }

private:
	// 렌더러와 빌더의 포인터 - 의존성 주입
	Renderer* renderer;
	Builder* builder;

	// 오브젝트 목록 - 추후 씬 그래프로 발전 예정
	std::vector<std::unique_ptr<SceneObject>> objects;	// 소유권 문제 고민 25. 5. 17.

};