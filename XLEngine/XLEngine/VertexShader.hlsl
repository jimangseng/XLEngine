cbuffer cbPerObject : register(b0)
{
	float4x4 WVPMatrix;
};


struct VS_In
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VS_Out
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

VS_Out main(VS_In vin)
{
	VS_Out vout;
	vout.position = mul(WVPMatrix, vin.position);
	vout.color = vin.color;
	
	return vout;
}