
struct a2v
{
	float3 position : ATTR0;
	float4 color	: ATTR1;
};

struct v2p
{
	float4 position : SV_POSITION;
	float4 color	: ATTR1;
};

v2p main(a2v input)
{
	v2p output;
	output.position = float4(input.position, 1.0);
	output.color = input.color;

	return output;
}