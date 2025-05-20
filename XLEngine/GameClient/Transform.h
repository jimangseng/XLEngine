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
	Math::Vector3 scale{ 1.0f, 1.0f, 1.0f};

public:
	Math::Matrix GetWorldMatrix() const { return Math::MakeWorldMatrix(position, rotation, scale); }
	Math::Matrix GetViewMatrix() const { return  Math::MakeViewMatrix(); }
	Math::Matrix GetProjectionMatrix() const { return Math::MakeProjectionMatrix(); }
	Math::Matrix GetWVPMatrix() const
	{
		return Math::MatrixMultiply(Math::MatrixMultiply(GetWorldMatrix(), GetViewMatrix()), GetProjectionMatrix());
	}

private:
	Math::Matrix worldMatrix;
	Math::Matrix viewMatrix;
	Math::Matrix wvpMatrix;
};