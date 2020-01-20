#include "SpriteShader.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_FadeTexture : register(t1);

SamplerState g_sampler : register(s0);
SamplerState g_FadeSamp : register(s1);

void main(SpritePS Input, out float4 Output : SV_TARGET)
{
    float4 Light = (saturate(Input.color) * Diffuse) + Emissive;
    Light.a = Diffuse.a;
    float4 Tex = g_texture.Sample(g_sampler, Input.tex);
    float4 Fade = float4(1.0f, 1.0f, 1.0f, 1.0f);
    if (FlagKeys.x==1)
    {
        Fade = g_FadeTexture.Sample(g_FadeSamp, Input.tex);
    }
    Light = lerp(Tex, Fade, paramf.x) * Light;
    Output = Light;
}