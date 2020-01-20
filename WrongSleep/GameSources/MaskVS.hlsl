//マスク用頂点シェーダー
#include "SpriteShader.hlsli"

void main(SpriteVS Input,out SpritePS Output)
{
    Output.position = mul(Input.position, MatrixTransform);
    Output.color = Input.color;
    Output.tex = Input.tex;
}