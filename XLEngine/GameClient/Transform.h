#pragma once
#include "MathTypes.h"

/*
* SceneObjectÀÇ ¸â¹ö Transform
* 25. 5. 19. jimangseng
*/
class Transform {
public:
	Math::Vector3 position;
	Math::Vector3 rotation;
	Math::Vector3 scale;

	Math::Matrix GetWorldMatrix() const {
		return Math::MakeWorldMatrix(position, rotation, scale);
	}
};