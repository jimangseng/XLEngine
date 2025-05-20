#pragma once
#include "DirectXMath.h"

/*
* DirectXMath¿« Wrapper
* 25. 5. 19. jimangseng
*/
namespace Math {
	using Vector3 = DirectX::XMFLOAT3;
	using Matrix = DirectX::XMMATRIX;

	Matrix MakeWorldMatrix(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale);
	Matrix MakeViewMatrix();
	Matrix MakeProjectionMatrix();

	Matrix MatrixMultiply(const Matrix& m1, const Matrix& m2);
}