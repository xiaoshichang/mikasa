cbuffer ConstantBufferPerScene : register(b0)
{
    float4 Arg1;
    float4 Arg2;
    float4 Arg3;
    float4 Arg4;
    float4 padding1[12];
};

cbuffer ConstantBufferPerView : register(b1)
{
    matrix ViewMatrix;
    matrix ProjectionMatrix;
    float4 padding2[8];
}

cbuffer ConstantBufferPerObject : register(b2)
{
    matrix WorldMatrix;
    float4 padding3[12];
};

cbuffer ConstantBufferPerDraw : register(b3)
{
    float4 pbr1;
    float4 pbr2;
    float4 pbr3;
    float4 pbr4;
    float4 padding4[12];
};

struct VSInput
{
    float3 Position : ATTRIBUTE0;
    float3 Normal   : ATTRIBUTE1;
    float3 Color    : ATTRIBUTE2;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : ATTRIBUTE2;
};

VSOutput main(VSInput input)
{
    VSOutput result;
    float4 hpos = float4(input.Position, 1);
    float4 wpos = mul(hpos, WorldMatrix);
    float4 vpos = mul(wpos, ViewMatrix);
    float4 cpos = mul(vpos, ProjectionMatrix);
    result.position = cpos;
    result.color = float4(input.Color, 1);

    return result;
}