#pragma once

class Geometry;
class Material;

/*
* 씬에 배치되는 오브젝트
* 25. 5. 17. jimangseng
*/
class SceneObject
{
public:
	SceneObject() = default;
	~SceneObject() = default;
	SceneObject(const SceneObject&) = default;
	SceneObject& operator= (const SceneObject&) = default;

private:
	// Transform transform;
	Geometry* geometry;
	Material* material;
};

