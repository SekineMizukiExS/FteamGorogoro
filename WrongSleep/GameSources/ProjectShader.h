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

	//�X�v���C�g�`��p
	DECLARE_DX11_VERTEX_SHADER(VSSprite,VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSSprite)

	//�}�X�N�p�R���X�^���g�o�b�t�@
	struct MaskCbuffer
	{		
		/// ���[���h�s��
		bsm::Mat4x4 World;
		/// �G�~�b�V�u�F
		bsm::Col4 Emissive;
		/// �f�t���[�Y�F
		bsm::Col4 Diffuse;

		XMUINT4 flags;
		MaskCbuffer(){
			memset(this, 0, sizeof(MaskCbuffer));
			Diffuse = bsm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
			flags = XMUINT4(0, 0, 0, 0);
		};

	};

	//�}�X�N�p�p�����[�^�o�b�t�@
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

