struct VS_INPUT
{
	float4 pos : POSITION;
	float3 color: COLOR;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 color: COLOR;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_projection;

	unsigned int m_time;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//output.pos = lerp(input.pos, input.pos1, (sin(m_angle) + 1.0f) / 2.0f);

	//WORLD SPACE
	output.pos = mul(input.pos, m_world);
	//VIEW SPACE
	output.pos = mul(output.pos, m_view);
	//SCREEN SPACE
	output.pos = mul(output.pos, m_projection);

	output.color = input.color;
	return output;
}