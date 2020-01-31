#include "SpriteShader.hlsli"

Texture2D g_texture : register(t0);
Texture2D g_FadeTexture : register(t1);

SamplerState g_sampler : register(s0);
SamplerState g_FadeSamp : register(s1);

void main(SpritePS Input, out float4 Output : SV_TARGET)
{
    //float4 Light = (saturate(Input.color) * Diffuse) + Emissive;
    //Light.a = Diffuse.a;
    float4 Tex = g_texture.Sample(g_sampler, Input.tex);
    //デフォルトでは黒フェード
    float4 Fade = float4(0.0f, 0.0f, 0.0f, 1.0f);
    if (FlagKeys.x==1)
    {
        Fade = g_FadeTexture.Sample(g_FadeSamp, Input.tex);
    }
    //フェード開始フラグ
    //フェードイン
    if(contlKeys.x ==1)
    {
        Output = lerp(Fade,float4(0.0, 0.0, 0.0, 0.0), paramf.x);
        return;
    }
    else if(contlKeys.x ==2)//フェードアウト
    {
        Output = lerp(float4(0.0, 0.0, 0.0, 0.0), Fade, paramf.x);
        return;
    }
    //マスクを適用する
    if (contlKeys.y == 1)
    {
        Output = Tex;
        return;
    }
    else if(contlKeys.y ==2)//動的変化をさせるマスク
    {
        float4 RedMask = Tex * float4(1, 0, 0, 1);
        Output = lerp(float4(0.0, 0.0, 0.0, 0.0), RedMask, paramf.y);
        return;
    }
    Output = float4(0, 0, 0, 0);
}