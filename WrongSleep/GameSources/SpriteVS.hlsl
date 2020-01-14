#include "SpriteShader.hlsli"

SpritePS main(SpriteVS input)
{
    SpritePS result;
    result.position = mul(input.position, MatrixTransform);
    result.color = input.color;
    result.tex = input.tex;

    return result;
}