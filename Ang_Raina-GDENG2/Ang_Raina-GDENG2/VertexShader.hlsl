struct VS_INPUT
{
	float4 pos : POSITION;
	float4 pos1 : POSITION1;
	float3 color: COLOR;
	float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_projection;

	//unsigned int m_time;
	float m_angle;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = lerp(input.pos, input.pos1, m_angle);

	//WORLD SPACE
	//output.pos = mul(input.pos, m_world);
	//VIEW SPACE
	//output.pos = mul(output.pos, m_view);
	//SCREEN SPACE
	//output.pos = mul(output.pos, m_projection);

	output.color = input.color;
	output.color1 = input.color1;
	return output;
}