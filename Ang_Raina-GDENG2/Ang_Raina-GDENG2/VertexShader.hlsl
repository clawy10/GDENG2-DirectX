struct VS_INPUT
{
	float4 pos : POSITION;
	float2 texcoord: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_projection;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//WORLD SPACE
	output.pos = mul(input.pos, m_world);
	//VIEW SPACE
	output.pos = mul(output.pos, m_view);
	//SCREEN SPACE
	output.pos = mul(output.pos, m_projection);

	output.texcoord = input.texcoord;
	return output;
}