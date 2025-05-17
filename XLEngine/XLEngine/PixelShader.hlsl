struct VS_Out
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

float4 main(VS_Out pin) : SV_TARGET
{
	return pin.color;
}