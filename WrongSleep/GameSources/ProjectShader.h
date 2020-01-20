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

	//マスク用コンスタントバッファ
	struct MaskCbuffer
	{		
		/// ワールド行列
		bsm::Mat4x4 World;
		/// エミッシブ色
		bsm::Col4 Emissive;
		/// デフューズ色
		bsm::Col4 Diffuse;

		XMUINT4 flags;
		MaskCbuffer(){
			memset(this, 0, sizeof(MaskCbuffer));
			Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
			flags = XMUINT4(0, 0, 0, 0);
		};

	};

	//マスク用パラメータバッファ
	struct MaskParamB
	{
		Vec4 param_f;
		XMUINT4 Flags;
		MaskParamB()
		{
			memset(this, 0, sizeof(MaskParamB));
			param_f = Vec4();
		}
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBMask, MaskCbuffer)
	DECLARE_DX11_CONSTANT_BUFFER(CBParamMask, MaskParamB)
	DECLARE_DX11_VERTEX_SHADER(VSMask, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSMask)

}
//end basecross

