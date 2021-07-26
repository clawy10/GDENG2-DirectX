struct PS_INPUT
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

float4 main(PS_INPUT input) : SV_TARGET
{
	return float4(input.color ,1.0f);
}