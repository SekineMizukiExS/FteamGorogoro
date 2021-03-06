/*!
@file ProjectShader.cpp
@brief プロジェクトで使用するシェーダー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	
	//エリアシェーダ
	//コンスタントバッファ
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBArea)
	//パラメータバッファ
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBParam)
	//頂点シェーダー
	IMPLEMENT_DX11_VERTEX_SHADER(VSFuton,App::GetApp()->GetShadersPath()+L"FutonVS.cso")
	//ピクセルシェーダ
	IMPLEMENT_DX11_PIXEL_SHADER(PSFuton,App::GetApp()->GetShadersPath()+L"FutonPS.cso")


	//スプライト描画用
	IMPLEMENT_DX11_VERTEX_SHADER(VSSprite,App::GetApp()->GetShadersPath()+L"SpriteVS.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSSprite, App::GetApp()->GetShadersPath() + L"SpritePS.cso")

	//マスク用
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBMask)
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBParamMask)
	//頂点シェーダー
	IMPLEMENT_DX11_VERTEX_SHADER(VSMask, App::GetApp()->GetShadersPath() + L"MaskVS.cso")
	//ピクセルシェーダ
	IMPLEMENT_DX11_PIXEL_SHADER(PSMask, App::GetApp()->GetShadersPath() + L"MaskPS.cso")

}
//end basecross


