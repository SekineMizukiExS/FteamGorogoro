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
		auto Device = App::GetApp()->GetInputDevice();
		auto Controller = Device.GetControlerVec()[0];

		float xAxis = 0.1f;
		float zAxis = 0.1f;

		if (Controller.bConnected)
		{
			xAxis = Controller.fThumbLX+0.1f;
			zAxis = Controller.fThumbLY+0.1f;
			Vec3 Axis(xAxis, 0, zAxis);
			float angle = sqrtf(xAxis*xAxis + zAxis * zAxis);
			auto TransComp = GetGameObject()->GetComponent<Transform>();
			bsm::Quat Qt(Axis, angle);
			TransComp->SetQuaternion(Qt);
			return;
		}

		auto KeyState = Device.GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			xAxis = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//��
			xAxis = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//���
			zAxis = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			zAxis = -1.0f;
		}

		Vec3 Axis(xAxis, 0, zAxis);
		float angle = sqrtf(xAxis*xAxis + zAxis * zAxis);
		auto TransComp = GetGameObject()->GetComponent<Transform>();
		bsm::Quat Qt(Axis, angle);
		TransComp->SetQuaternion(Qt);
		return;
	}

	//float AreaBehavior::ExeTime(float nowtime)
	//{
	//}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			ret.x = 1.0f;
		}
		return ret;
	}

	//�i�s�x�N�g���ւ̉��@�֐�
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//���͂̎擾
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			//Y���͕ω������Ȃ�
			angle.y = 0;
		}
		return angle;
	}

	void Player::MovePlayer() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}
}

//end basecross

