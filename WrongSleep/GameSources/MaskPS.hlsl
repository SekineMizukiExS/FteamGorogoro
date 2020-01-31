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
    //�f�t�H���g�ł͍��t�F�[�h
    float4 Fade = float4(0.0f, 0.0f, 0.0f, 1.0f);
    if (FlagKeys.x==1)
    {
        Fade = g_FadeTexture.Sample(g_FadeSamp, Input.tex);
    }
    //�t�F�[�h�J�n�t���O
    //�t�F�[�h�C��
    if(contlKeys.x ==1)
    {
        Output = lerp(Fade,float4(0.0, 0.0, 0.0, 0.0), paramf.x);
        return;
    }
    else if(contlKeys.x ==2)//�t�F�[�h�A�E�g
    {
        Output = lerp(float4(0.0, 0.0, 0.0, 0.0), Fade, paramf.x);
        return;
    }
    //�}�X�N��K�p����
    if (contlKeys.y == 1)
    {
        Output = Tex;
        return;
    }
    else if(contlKeys.y ==2)//���I�ω���������}�X�N
    {
        float4 RedMask = Tex * float4(1, 0, 0, 1);
        Output = lerp(float4(0.0, 0.0, 0.0, 0.0), RedMask, paramf.y);
        return;
    }
    Output = float4(0, 0, 0, 0);
}