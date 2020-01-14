/*!
@file ProjectShader.cpp
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	
	//�G���A�V�F�[�_
	//�R���X�^���g�o�b�t�@
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBArea)
	//�p�����[�^�o�b�t�@
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBParam)
	//���_�V�F�[�_�[
	IMPLEMENT_DX11_VERTEX_SHADER(VSFuton,App::GetApp()->GetShadersPath()+L"FutonVS.cso")
	//�s�N�Z���V�F�[�_
	IMPLEMENT_DX11_PIXEL_SHADER(PSFuton,App::GetApp()->GetShadersPath()+L"FutonPS.cso")


	//�X�v���C�g�`��p
	IMPLEMENT_DX11_VERTEX_SHADER(VSSprite,App::GetApp()->GetShadersPath()+L"SpriteVS.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSSprite, App::GetApp()->GetShadersPath() + L"SpritePS.cso")
}
//end basecross


