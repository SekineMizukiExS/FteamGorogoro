#include "AreaShader.hlsli"

FutonPS main(FutonVS input)
{
    FutonPS result;
    
    float4 pos = float4(input.pos.xyz, 1.0f);

    pos = mul(pos, World);

    pos = mul(pos, View);

    pos = mul(pos, Projection);

    result.pos = pos;

    result.norm = mul(input.norm, (float3x3) World);
    result.norm = normalize(result.norm);

    result.tex = input.tex;
    return result;
}