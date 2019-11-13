/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include <experimental/generator>

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

		//���]
		bool m_reverse = false;

		float m_PlayerSpeed = 0;
		Vec3 m_ChargedVec = Vec3(0,0,0);

		//���W
		Vec3 nowPos = Vec3(0, 0, 0);

		//�X�e�[�g�}�V��
		unique_ptr<StateMachine<Player>> m_stateMachine;

		//======��]�R���[�`���p========
		//��]��
		bool isRotate = false;
		float cubeSizeHalf = 0;
		float cubeAngle = 15;
		Vec3 rotatePoint = Vec3(0, 0, 0);
		Vec3 rotateAxis = Vec3(0, 0, 0);



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

		std::experimental::generator<int>  MoveCube()
		{
			//��]���̃t���O�𗧂Ă�
			isRotate = true;

			auto transptr = GetComponent<Transform>();
			Quat tempQ = transptr->GetQuaternion();
			Vec3 pivot = Vec3(0, -2, 0);
			Vec3 exam = Vec3(1, 0, 0);
			Vec3 exPos(0, 0, 0);

			//��]����
			float sumAngle = 0.0f; //angle�̍��v��ۑ�
			while (sumAngle < 90.0f)
			{
				cubeAngle = 15.0f; //������ς���Ɖ�]���x���ς��
				sumAngle += cubeAngle;

				// 90�x�ȏ��]���Ȃ��悤�ɒl�𐧌�
				if (sumAngle > 180.0f)
				{
					cubeAngle -= sumAngle - 180.0f;
				}
				transptr->RotateAround(rotatePoint, rotateAxis, cubeAngle,tempQ, exPos);

				co_yield 0;
			}

			//��]���̃t���O��|��
			isRotate = false;
			rotatePoint = Vec3(0, 0, 0);
			rotateAxis = Vec3(0, 0, 0);
			//PlColEve.PlaySound(0);

			co_return;
		}

	};

}
//end basecross

