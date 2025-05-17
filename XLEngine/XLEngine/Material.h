#pragma once

class D3D11Core;

/*
* 쉐이더 및 머티리얼 관련 
* 25. 5. 15. jimangseng
*/
class Material
{
public:
	Material() = default;
	~Material() = default;
	Material(const Material&) = default;
	Material& operator= (const Material&) = default;

public:
	bool Initialize(const D3D11Core& _core, const WCHAR* _vsBlobPath, const WCHAR* _psBlobPath);
	bool Finalize();

public:
	ID3DBlob* GetVSBlob() const { return vsBlob.get(); }
	ID3DBlob* GetPSBlob() const { return psBlob.get(); }

private:
	winrt::com_ptr<ID3DBlob> vsBlob;
	winrt::com_ptr<ID3DBlob> psBlob;
};

