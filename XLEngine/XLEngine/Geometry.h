#pragma once

#include "D3D11Core.h"

/*
* 지오메트리 (VB, IB) 관련
* 25. 5. 15. jimangseng
*/
class Geometry
{
public:
	Geometry() = default;
	~Geometry() = default;
	Geometry(const Geometry&) = default;	// todo: 복사생성자, 복사 대입 연산자 구현하기
	Geometry& operator= (const Geometry&) = default;

public:
	bool Initialize();
	bool Finalize();

public:
	// Getter
	size_t GetNumIndices() const { return numIndices; }
	const UINT &GetStride() { return stride; }
	const UINT &GetOffset() { return offset; }
	ID3D11Buffer* GetVB() const { return vertexBuffer.get(); }
	ID3D11Buffer* GetIB() const { return indexBuffer.get(); }

	// Setter
	void SetNumIndices(size_t _numIndices) { numIndices = _numIndices; }
	void SetStride(UINT _stride) { stride = _stride; }
	void SetOffset(UINT _offset) { offset = _offset; }
	void SetVB(winrt::com_ptr<ID3D11Buffer> _VB) { vertexBuffer = _VB; }
	void SetIB(winrt::com_ptr<ID3D11Buffer> _IB) { indexBuffer = _IB; }

private:
	// VB 관련
	winrt::com_ptr<ID3D11Buffer> vertexBuffer;
	UINT stride;
	UINT offset;

	// IB 관련
	winrt::com_ptr<ID3D11Buffer> indexBuffer;
	size_t numIndices;
};