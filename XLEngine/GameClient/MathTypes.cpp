#include "MathTypes.h"

Math::Matrix Math::MakeWorldMatrix(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale)
{
	// todo: 구현하기 25. 5. 19.
	// world matrix를 구하는 것은 여기가 아니라, Transform에 있어야 함. MathTypes는 단순히 DirectXMath에 대한 wrapper여야 한다.

	using namespace DirectX;

	XMVECTOR position = XMLoadFloat3(&_position);
	XMVECTOR rotation = XMLoadFloat3(&_rotation);
	XMVECTOR scale = XMLoadFloat3(&_scale);

	XMMATRIX translationMatrix = XMMatrixTranslationFromVector(position);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYawFromVector(rotation);
	XMMATRIX scaleMatrix = XMMatrixScalingFromVector(scale);

	XMMATRIX worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, rotationMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, translationMatrix);

	return worldMatrix;
}

Math::Matrix Math::MakeViewMatrix()
{
	using namespace DirectX;

	Math::Vector3 cameraPosition{ 0.0f, 0.0f, -1.0f };
	Math::Vector3 cameraDirection{ 0.0f, 0.0f, 1.0f };
	Math::Vector3 up{ 0.0f, 1.0f, 0.0f };

	XMVECTOR camPosMat{ XMLoadFloat3(&cameraPosition) };
	XMVECTOR camDirMat{ XMLoadFloat3(&cameraDirection) };
	XMVECTOR upMat{ XMLoadFloat3(&up) };

	return XMMatrixLookToLH(camPosMat, camDirMat, upMat);
}

Math::Matrix Math::MakeProjectionMatrix()
{
	return DirectX::XMMatrixPerspectiveFovLH(45.0f, 1.0f, 0.01f, 10.0f);
}

Math::Matrix Math::MatrixMultiply(const Matrix& m1, const Matrix& m2)
{
	return DirectX::XMMatrixMultiply(m1, m2);
}
