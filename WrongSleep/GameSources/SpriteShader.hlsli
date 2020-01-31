//�X�v���C�g�`��p
cbuffer ConstantBuffer : register(b0)
{
    row_major float4x4 MatrixTransform : packoffset(c0);
    float4 Emissive : packoffset(c4);
    float4 Diffuse : packoffset(c5);
    uint4 FlagKeys : packoffset(c6);
};

cbuffer MaskParam : register(b1)
{
    //�V�F�[�_�[����p�p�����[�^
    //param.x = �t�F�[�h��ԌW���i0�`1�j
    //param.y = �}�X�N�p��ԌW���i0�`1)  
    float4 paramf : packoffset(c0);
    //�V�F�[�_�[����p�R���g���[���L�[
    //contlKeys.x = �t�F�[�h�R���g���[���p
    //contlKeys.y = �}�X�N����p
    uint4 contlKeys : packoffset(c1);
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