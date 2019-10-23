/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {

	public:
		//�\�z�Ɣj��
//--------------------------------------------------------------------------------------
/*!
@brief	�R���X�g���N�^
@param[in]	StagePtr	�X�e�[�W
*/
//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);

		//������
		virtual void OnCreate() override;
		//�X�V
		//virtual void OnUpdate() override;
	};

}
//end basecross

