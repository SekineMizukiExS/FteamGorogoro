//スプライト描画用
cbuffer ConstantBuffer : register(b0)
{
    row_major float4x4 MatrixTransform : packoffset(c0);
    float4 Emissive : packoffset(c4);
    float4 Diffuse : packoffset(c5);
};

cbuffer SpriteParam : register(b1)
{
    uint4 flags : packoffset(c0);
};

struct SpriteVS
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

struct SpritePS
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};