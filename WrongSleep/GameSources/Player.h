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
		Vec2 GetInputState() const;
		Vec3 GetMoveVector() const;
		void MovePlayer();
		//������̕\��
		void DrawStrings();


		//�R���g���[���̔ԍ�
		const int m_cntlNum;
		//����n
		Controller m_cntl;
		bool Tempbool = false;
		Vec3 TempPivot;
		//��
		float m_time = 0;
		//�X�s�[�h
		float m_Speed = 1;
		//���̓n���h���[
		InputHandler<Player> m_inputHandler;
		wstring m_sharedName;

		float m_PlayerSpeed = 0;
		Vec3 m_ChargedVec = Vec3(0,0,0);

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

		void DebugLine();

		/*!
@brief	������W�𒆐S�ɉ�]����
@return	�Ȃ�
*/
		//--------------------------------------------------------------------------------------
		bool RotateAround(const bsm::Vec3& point, const bsm::Vec3& axis, float angle, shared_ptr<Transform> tr,bool onoff);
		//--------------------------------------------------------------------------------------
	};

}
//end basecross

