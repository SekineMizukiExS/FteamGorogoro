//�}�X�N�p���_�V�F�[�_�[
#include "SpriteShader.hlsli"

void main(SpriteVS Input,out SpritePS Output)
{
    Output.position = mul(Input.position, MatrixTransform);
    Output.color = Input.color;
    Output.tex = Input.tex;
}