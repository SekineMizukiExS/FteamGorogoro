/*!
@file ProjectShader.h
@brief プロジェクトで使用するシェーダー
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//エリア用コンスタントバッファ
	struct AreaCB
	{
		Mat4x4 World;
		Mat4x4 View;
		Mat4x4 Projection;
		Col4 Emissive;
		Col4 Diffuse;
		Vec4 LightDir;
		XMUINT4 ActiveFlg;
		AreaCB() {
			memset(this, 0, sizeof(AreaCB));
			Diffuse = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			ActiveFlg = XMUINT4(0, 0, 0, 0);
		};

	};

	//シェーダーに渡すパラメータ
	struct ParamCB
	{
		Vec4 param_f;
		XMUINT4 Flags;
		ParamCB()
		{
			memset(this, 0, sizeof(ParamCB));
			param_f = Vec4();
			Flags = XMUINT4();
		}
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBArea, AreaCB)
	DECLARE_DX11_CONSTANT_BUFFER(CBParam,ParamCB)
	DECLARE_DX11_VERTEX_SHADER(VSFuton,VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSFuton)

	//スプライト描画用
	DECLARE_DX11_VERTEX_SHADER(VSSprite,VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSSprite)
}
//end basecross

