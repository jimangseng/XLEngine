#pragma once

#include "D3D11Core.h"
#include "Geometry.h"
#include "Material.h"

/*
* Geometry와 Material 객체를 생성해주는 엔진 요소
* 오직 생성만 하고, 바인드는 renderer가 한다.
* 25. 5. 19. jimangseng
*/
class Builder
{
public:
	Builder() = default;
	~Builder() = default;
	Builder(const Builder&) = delete;
	Builder& operator= (const Builder&) = delete;

public:
	void Initialize(D3D11Core& _core);

public:
	std::unique_ptr<Geometry> BuildGeometry(const std::vector<Geometry::Vertex>& _vertices, const std::vector<UINT32>& _indices) const;
	std::unique_ptr<Material> BuildMaterial(std::vector<D3D11_INPUT_ELEMENT_DESC>) const;

private:
	D3D11Core* core;
};