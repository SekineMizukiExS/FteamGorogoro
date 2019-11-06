/*!
@file ProjectBehavior.cpp
@brief プロジェク定義の行動クラス実体
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

	//未実装
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
			//現在の回転を取得
			bsm::Quat NowQt = TransComp->GetQuaternion();
			//現在と目標を補間
			//現在と目標を補間
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

	//float AreaBehavior::ExeTime(float nowtime)
	//{
	//}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			ret.y = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			ret.x = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			ret.y = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
			ret.x = 1.0f;
		}
		return ret;
	}
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
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
		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}
}

//end basecross

