#include "AreaShader.hlsli"

Texture2D g_MainTex : register(t0);
SamplerState s_MainSamp : register(s0);


float4 main(FutonPS input):SV_TARGET
{
    float4 result = float4(1, 1, 1, 1);
    if(Activeflags.x==1)
        result = g_MainTex.Sample(s_MainSamp, input.tex);
    return result;
}