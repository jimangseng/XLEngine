#pragma once

class D3D11Core;

/*
* ½¦ÀÌ´õ ¹× ¸ÓÆ¼¸®¾ó °ü·Ã 
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
	bool Initialize(const WCHAR* _vsBlobPath, const WCHAR* _psBlobPath);
	bool Finalize();

public:
	// Getter
	ID3DBlob* GetVSBlob() const { return vsBlob.get(); }
	ID3DBlob* GetPSBlob() const { return psBlob.get(); }
	ID3D11VertexShader* GetVS() const { return vertexShader.get(); }
	ID3D11PixelShader* GetPS() const { return pixelShader.get(); }
	ID3D11InputLayout* GetInputLayout() const { return inputLayout.get(); }

	// Setter
	void SetVSBlob(winrt::com_ptr<ID3DBlob> _vsBlob) { vsBlob = _vsBlob; }
	void SetPSBlob(winrt::com_ptr<ID3DBlob> _psBlob) { psBlob = _psBlob; }
	void SetVS(winrt::com_ptr<ID3D11VertexShader> _VS) { vertexShader = _VS;}
	void SetPS(winrt::com_ptr<ID3D11PixelShader> _PS) { pixelShader = _PS; }
	void SetInputLayout(winrt::com_ptr<ID3D11InputLayout> _inputLayout) { inputLayout = _inputLayout; }

private:
	// shader bytecode
	winrt::com_ptr<ID3DBlob> vsBlob;
	winrt::com_ptr<ID3DBlob> psBlob;

	// shader d3d °´Ã¼
	winrt::com_ptr<ID3D11VertexShader> vertexShader;
	winrt::com_ptr<ID3D11PixelShader> pixelShader;

	// input layout °´Ã¼
	winrt::com_ptr<ID3D11InputLayout> inputLayout;
};

