/*!=
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "ObjUtil.h"
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
		//��
		float m_time = 0;
		//�X�s�[�h
		float m_speed = 0.25f;
		float m_inputCooltime = 0.15f;//�ē��͂܂ł̑ҋ@����
		//���̓n���h���[
		InputHandler<Player> m_inputHandler;
		wstring m_sharedName;

		//���]
		bool m_reverse = false;

		//���W
		Vec3 m_nowPos = Vec3(0, 0, 0);
		Vec3 m_beforePos = Vec3(0, 0, 0);

		//�X�e�[�g�}�V��
		unique_ptr<StateMachine<Player>> m_stateMachine;

		//======��]�R���[�`���p========
		//��]��
		bool m_isRotate = false;
		float m_cubeAngle = 15;
		Vec3 m_rotatePoint = Vec3(0, 0, 0);
		Vec3 m_rotateAxis = Vec3(0, 0, 0);

		//�ڒn�ʂ̎l�ӂ��i�[���Ēu���\����
		Vec3HalfSizes m_V3HS = {0};
		Vec3 m_Buttom = Vec3(0,0,0);
		vector<VertexPosition> m_ButtomVertexs;

		float m_groundLine = 0;

		Vec3 m_nowSize = Vec3(1, 1, 1);

		int m_count = 0;
		int angleCount[7];
		int m_vCount = 0;
		int m_usingSize = 3;//���ݎg�p�\�ȃT�C�Y�e�ʁA�Q�������l

		shared_ptr<EfkPlay> m_EfkPlay;

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
		//�ڐG����
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void DebugLine();
		//�ڒn�ʂ̎l�ӂ��擾���A�����o�ϐ��ɑ������B
		void GetInFourEdge();
		void GetInFourEdge(bool bcheck);
		//��]�ړ�
		void RotateMove();
		//�L�т�
		void BoxExtending();
		//�����L�т�������擾
		Vec3 GetExtendingAngle();
		//��]����擾����֐�
		Vec3 GetRotateVector();

		//�d�͏���
		void Gravity2();

		//�v���C���[�̍ŏ��̒�ʂ��擾����֐�
		


		/*
		std::experimental::generator<int>  MoveCube()
		{
			//��]���̃t���O�𗧂Ă�
			m_isRotate = true;

			auto transptr = GetComponent<Transform>();
			Quat tempQ = transptr->GetQuaternion();
			Vec3 pivot = Vec3(0, -2, 0);
			Vec3 exam = Vec3(1, 0, 0);
			Vec3 exPos(0, 0, 0);

			//��]����
			float sumAngle = 0.0f; //angle�̍��v��ۑ�
			while (sumAngle < 90.0f)
			{
				m_cubeAngle = 15.0f; //������ς���Ɖ�]���x���ς��
				sumAngle += m_cubeAngle;

				// 90�x�ȏ��]���Ȃ��悤�ɒl�𐧌�
				if (sumAngle > 180.0f)
				{
					m_cubeAngle -= sumAngle - 180.0f;
				}
				transptr->RotateAround(m_rotatePoint, m_rotateAxis, m_cubeAngle,tempQ, exPos);

				co_yield 0;
			}

			//��]���̃t���O��|��
			m_isRotate = false;
			m_rotatePoint = Vec3(0, 0, 0);
			m_rotateAxis = Vec3(0, 0, 0);
			//PlColEve.PlaySound(0);

			co_return;
		}
		*/
	};


	class PlayerMarker : public GameObject {

	private:
		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
	public:
		/*!
		@brief	�Ǐ]�ڕW�I�u�W�F�N�g�𓾂�
		@return	�Ǐ]�ڕW
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObject> GetTargetObject() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Ǐ]�ڕW�I�u�W�F�N�g��ݒ肷��
		@param[in]	Obj	�Ǐ]�ڕW�I�u�W�F�N�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------

		PlayerMarker(const shared_ptr<Stage>& StagePtr);

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};

	class PlayerModel : public GameObject {

	private:
		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
	public:
		/*!
		@brief	�Ǐ]�ڕW�I�u�W�F�N�g�𓾂�
		@return	�Ǐ]�ڕW
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObject> GetTargetObject() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Ǐ]�ڕW�I�u�W�F�N�g��ݒ肷��
		@param[in]	Obj	�Ǐ]�ڕW�I�u�W�F�N�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------

		PlayerModel(const shared_ptr<Stage>& StagePtr);

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}
//end basecross

