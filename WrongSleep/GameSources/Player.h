/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
	private:
		//--------------------------------------//
//----�R���g���[���A�V�X�e�����̕ϐ�----//
//--------------------------------------//

		// �R���g���[����������x�N�g���𓾂�
		Vec3 GetMoveVector() const;
		//������̕\��
		void DrawStrings();

		//�R���g���[���̔ԍ�
		const int m_cntlNum;
		//����n
		Controller m_cntl;
		//���̓n���h���[
		InputHandler<Player> m_inputHandler;
		wstring m_sharedName;

		//�X�e�[�g�}�V��
		unique_ptr<StateMachine<Player>> m_stateMachine;



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
		virtual void OnUpdate() override;
	};

}
//end basecross
