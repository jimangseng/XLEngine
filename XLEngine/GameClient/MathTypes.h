#pragma once
#include "DirectXMath.h"

/*
* DirectXMath¿« Wrapper
* 25. 5. 19. jimangseng
*/
namespace Math {
	using Vector3 = DirectX::XMFLOAT3;
	using Matrix = DirectX::XMMATRIX;

	inline Matrix MakeWorldMatrix(const Vector3& pos, const Vector3& rot, const Vector3& scale);
}