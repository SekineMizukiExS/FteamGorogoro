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

}
//end basecross


