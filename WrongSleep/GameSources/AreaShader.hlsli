/*!
@file AreaShader.hlsli
@breif �V�F�[�_�p�܂Ƃ�
*/
cbuffer AreaCB:register(b0)
{
    float4x4 World : packoffset(c0);
    float4x4 View : packoffset(c4);
    float4x4 Projection : packoffset(c8);
    float4 Emissive : packoffset(c12);
    float4 Diffuse : packoffset(c13);
    float4 LightDir : packoffset(c14);
    uint4 Activeflags : packoffset(c17); //�t���O
};

//�e��p�����[�^
cbuffer ParamCB : register(b1)
{
    float4 Time : packoffset(c0);
};

struct FutonVS
{
    float4 pos : SV_POSITION;
    float3 norm : NORMAL;
    float2 tex : TEXCOORD;
};

struct FutonPS
{
    float4 pos : SV_POSITION;
    float3 norm : NORMAL;
    float2 tex : TEXCOORD;
};