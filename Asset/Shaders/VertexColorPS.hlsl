struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : ATTRIBUTE2;
};

float4 main(PSInput input) : SV_TARGET
{
    return input.color;
}