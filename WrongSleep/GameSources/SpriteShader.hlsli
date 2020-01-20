//スプライト描画用
cbuffer ConstantBuffer : register(b0)
{
    row_major float4x4 MatrixTransform : packoffset(c0);
    float4 Emissive : packoffset(c4);
    float4 Diffuse : packoffset(c5);
    uint4 FlagKeys : packoffset(c6);
};

cbuffer MaskParam : register(b1)
{
    //シェーダー制御用パラメータ
    //param.x = フェード補間係数（0～1）
    float4 paramf : packoffset(c0);
    
}

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