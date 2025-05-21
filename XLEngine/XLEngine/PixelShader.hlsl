struct VS_Out
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

float4 main(VS_Out pin) : SV_TARGET
{

	//float3 color = pow(pin.color.xyz, 1.0 / 2.2); // 수동 감마
	//return float4(color, 1.0);
	return pin.color;
}