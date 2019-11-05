/*!
@file ProjectBehavior.cpp
@brief �s���N���X����
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	void AreaBehavior::SetInputCode(const int &CODE = NULL)
	{
		switch (CODE)
		{
		case INPUT_CODE_ROT:
			Rot();
			break;
		case INPUT_CODE_MOVE:
			Move();
			break;
		case INPUT_CODE_HUMAN:
			InputController();
			break;
		default:
			break;
		}
	}

	void AreaBehavior::Move()
	{
		const float TotalTime = 2.0f;

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		_ptime += ElapsedTime;
		if (TotalTime < _ptime) {
			_ptime = 0;
			_moveb = !_moveb;
			return;
		}
		auto obj = GetGameObject();
		auto TransComp = obj->GetComponent<Transform>();
		const float Force = 2.0f;
		Vec3 Pos = TransComp->GetPosition();

		Pos.x += _moveb ? Force * ElapsedTime : -Force * ElapsedTime;

		TransComp->SetPosition(Pos);
	}


	void AreaBehavior::Rot()
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();

		const float LerpFact = 1.0f;
		const float TotalTime = 2.0f;

		auto obj = GetGameObject();
		auto TransComp = obj->GetComponent<Transform>();
		const float Rad = XM_PI;

		switch (_rotsw)
		{
		case basecross::AreaBehavior::SwitchIO::Stop:
			_rtime += ElapsedTime;
			if (TotalTime > _rtime) {
				return;
			}
			_rotb = !_rotb;
			_rotsw = SwitchIO::Excute;
			_rtime = 0;
			break;
		case basecross::AreaBehavior::SwitchIO::Excute:

			_rotval += _rotb ? +Rad * ElapsedTime : -Rad * ElapsedTime;
			bsm::Quat Qt;
			Qt.rotationRollPitchYawFromVector(bsm::Vec3(_rotval, 0, 0));
			Qt.normalize();

			bsm::Quat NowQt = TransComp->GetQuaternion();

			if (LerpFact >= 1.0f) {
				NowQt = Qt;
			}
			else {
				NowQt = XMQuaternionSlerp(NowQt, Qt, LerpFact);
			}
			TransComp->SetQuaternion(NowQt);

			CheckQuat(_rotval);

			break;
		}

	}

	void AreaBehavior::CheckQuat(const float CheckVal)
	{
		if (fabs(CheckVal)>_MaxQuat)
		{
			_rotsw = SwitchIO::Stop;
		}
	}
	
	//------------------------------------
	///2P���͗p
	//------------------------------------
	void AreaBehavior::InputController()
	{

	}

	//float AreaBehavior::ExeTime(float nowtime)
	//{
	//}

	//�i�s�x�N�g���ւ̉��@�֐�
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		float moveLength = 0;	//���������̃X�s�[�h
		auto ptrTransform = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		//�i�s�����̌������v�Z
		auto front = ptrTransform->GetWorldPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//�i�s������������̊p�x���Z�o
		float frontAngle = atan2(front.z, front.x);
		//�R���g���[���̌����v�Z
		float moveX = m_cntl.LX;
		float moveY = m_cntl.LY;

		Vec2 moveVec(moveX, moveY);
		float moveSize = moveVec.length();
		//�R���g���[���̌�������p�x���v�Z
		float cntlAngle = atan2(-moveX, moveY);
		//�g�[�^���̊p�x���Z�o
		float totalAngle = frontAngle + cntlAngle;
		//�p�x����x�N�g�����쐬
		angle = Vec3(cos(totalAngle), sin(totalAngle), 0);
		//���K������
		angle.normalize();
		//�ړ��T�C�Y��ݒ�B
		angle *= moveSize;
		//Z���͕ω������Ȃ�
		angle.z = 0;
		return angle;

	}

	//�v���C���[�̈ړ�����
	void Player::MovePlayer() {
		//float elapsedTime = App::GetApp()->GetScene<Scene>()->GetElpasedTime();
		Vec3 m_PlayerAngle = GetMoveVector();
		float elapsedTime = 1;


		////�����ړ�
		float m_addSpeed = 5;
		auto ThisT = GetComponent<Transform>();
		Vec3 m_playerPos = ThisT->GetPosition();
		float m_playerScale = ThisT->GetScale().x;
		auto velocity = m_PlayerAngle * m_PlayerSpeed * 5 * m_playerScale * m_addSpeed * elapsedTime;
		//Vec3 m_velocity; += velocity;

		m_ChargedVec += velocity;
		//�w��n�_�ւ̈���
		Vec3 velocity2 = m_ChargedVec - m_playerPos;
		float dis2 = length(velocity2);
		velocity2 = normalize(velocity2);
		//���͎w�肪�s���߂��Ȃ��悤�ɒ���
		m_playerPos += velocity2 * m_PlayerSpeed * dis2 *elapsedTime;
		ThisT->SetPosition(m_playerPos);
	}
}

//end basecross

