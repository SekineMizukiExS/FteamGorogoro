#include "AreaShader.hlsli"

Texture2D g_MainTex : register(t0);
SamplerState s_MainSamp : register(s0);


float4 main(FutonPS input):SV_TARGET
{
    float4 Mc = g_MainTex.Sample(s_MainSamp, input.tex);

    return Mc;
}