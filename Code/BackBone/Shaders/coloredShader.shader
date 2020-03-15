struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer cbPerObject
{
    float4x4 wvp;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(position, wvp);
    output.color = color;

    return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}