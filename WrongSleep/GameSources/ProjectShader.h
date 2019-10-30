/*!
@file ProjectShader.h
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//�G���A�p�R���X�^���g�o�b�t�@
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

	//�V�F�[�_�[�ɓn���p�����[�^
	struct ParamCB
	{
		Vec4 param_f;

		ParamCB()
		{
			memset(this, 0, sizeof(ParamCB));
			param_f = Vec4();
		}
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBArea, AreaCB)
	DECLARE_DX11_CONSTANT_BUFFER(CBParam,ParamCB)
	DECLARE_DX11_VERTEX_SHADER(VSFuton,VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSFuton)
}
//end basecross
