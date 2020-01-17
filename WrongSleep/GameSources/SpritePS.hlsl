#include "SpriteShader.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_BackTex : register(t1);

SamplerState g_sampler : register(s0);
SamplerState g_BackSamp : register(s1);

float4 main(SpritePS input) : SV_TARGET
{
    float4 Light = (saturate(input.color) * Diffuse) + Emissive;
    Light.a = Diffuse.a;
    float4 Tex = g_texture.Sample(g_sampler, input.tex);
    float4 BackTex = g_BackTex.Sample(g_BackSamp, input.tex);
    Light = lerp(Tex, BackTex, BackTex.a) * Light;
    return Light;
}