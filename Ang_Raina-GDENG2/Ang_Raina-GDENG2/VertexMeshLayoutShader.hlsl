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

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = input.pos;
	output.texcoord = input.texcoord;
	return output;
}