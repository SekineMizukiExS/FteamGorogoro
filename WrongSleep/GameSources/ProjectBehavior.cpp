/*!
@file ProjectBehavior.cpp
@brief 行動クラス実体
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
	///2P入力用
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
			//前
			xAxis = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//左
			xAxis = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//後ろ
			zAxis = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
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

	//進行ベクトルへの加法関数
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

	//-------------------------------------------------------------
	///エネミー行動クラス実装
	//-------------------------------------------------------------
	//struct TravelingPoint;
	bool EnemyBehavior::TravelingMove()
	{
		//float ElapsedTime = App::GetApp()->GetElapsedTime();
		//_TotalTime += ElapsedTime;
		//if (_TotalTime > MoveTime) {
		//	_TotalTime = 0;
		//	return true;
		//}
		//Easing<Vec3> easing;
		//auto MoveForce = easing.EaseInOut(EasingType::Cubic, _CurrntPos, _MovePoint, _TotalTime, MoveTime);
		////auto MoveForce = _MovePoint - _CurrntPos;
		////MoveForce.normalize();
		//RotateMove(MoveForce);
		return RotateMove();
	}

	bool EnemyBehavior::TrackingMove()
	{
		if (_TargetObject)
		{
			_MovePoint = _TargetObject->GetComponent<Transform>()->GetPosition();
		}
		return RotateMove();
	}

	void EnemyBehavior::SetNextPoint()
	{
		auto TransComp = GetGameObject()->GetComponent<Transform>();
		auto EnemyObj = dynamic_pointer_cast<EnemyBase>(GetGameObject());

		_MovePoint = GetPoint(TransComp->GetPosition(), EnemyObj->GetTravelingPoint());
	}

	Vec3 EnemyBehavior::GetPoint(const Vec3& CurrntPosition, const vector<TravelingPoint>& Point)
	{
		Vec3 result(0);
		if (Point[_NextKey] == Point.back())
		{
			_TestMove = false;
		}
		else if (Point[_NextKey] == Point.front())
		{
			_TestMove = true;
		}
		result = Point[_NextKey].Point;
		_NextKey = _TestMove ? Point[_NextKey].after:Point[_NextKey].before;
		_CurrntPos = CurrntPosition;
		return result;
	}

	//移動関数
	bool EnemyBehavior::RotateMove()
	{
		auto TransComp = GetGameObject()->GetComponent<Transform>();
		auto DrawComp = GetGameObject()->GetComponent<AreaDraw>();
		Vec3HalfSizes Test;
		Vec3 nowPos = TransComp->GetPosition();
		float maxrot = 0.5f * XM_PI;

		//Key判定
		if (Search(_MovePoint))
		{
			//めり込み直し
			if (TransComp->GetPosition().y <= 0.5f) {
				auto temppos = TransComp->GetPosition();
				TransComp->SetPosition(temppos.x, 0.5f, temppos.z);
			}
			if (_RotActive) {
				if (_count < 5) {
					TransComp->RotateAround(_RotPoint, _RotAxis, 0.1f * XM_PI, nowPos);
					_count += 1;
				}
				else {

					_count = 0;
					_RotActive = false;

				}
			}
			else
			{
				//NextCellのXZを比較する
				//小さいほうから操作
				if (_CellIndex == _TargetCellIndex) return true;

				auto X = _CellPath[_NextCellIndex].x - _CellPath[_CellIndex].x;
				auto Z = _CellPath[_NextCellIndex].z - _CellPath[_CellIndex].z;

				if (abs(X) > abs(Z))
				{
					//X
					if (X > 0)//+
					{
						Test.GetFourEdge(TransComp, DrawComp);
						nowPos = TransComp->GetPosition();
						_RotPoint = Vec3(Test._xHalfSize, Test._yHalfSizeMin, 0.0f);
						_RotAxis = Vec3(0, 0, 1);
						_RotActive = true;
					}
					else if (X < 0)//-
					{
						Test.GetFourEdge(TransComp, DrawComp);
						nowPos = TransComp->GetPosition();
						_RotPoint = Vec3(Test._xHalfSizeMin, Test._yHalfSizeMin, 0.0f);
						_RotAxis = Vec3(0, 0, -1);
						_RotActive = true;

					}
				}
				else
				{
					//Z
					if (Z > 0)//+
					{
						Test.GetFourEdge(TransComp, DrawComp);
						nowPos = TransComp->GetPosition();
						_RotPoint = Vec3(0.0f, Test._yHalfSizeMin, Test._zHalfSize);
						_RotAxis = Vec3(-1, 0, 0);
						_RotActive = true;

					}
					else if (Z < 0)//-
					{
						Test.GetFourEdge(TransComp, DrawComp);
						nowPos = TransComp->GetPosition();
						_RotPoint = Vec3(0.0f, Test._yHalfSizeMin, Test._zHalfSizeMin);
						_RotAxis = Vec3(1, 0, 0);
						_RotActive = true;
					}

				}
			}
		}
		else
			return true;
		//エネミーのAABB
		Test.GetFourEdge(TransComp, DrawComp);
		AABB TestAABB = AABB(Vec3(Test._xHalfSizeMin, Test._yHalfSizeMin, Test._zHalfSizeMin), Vec3(Test._xHalfSize, Test._yHalfSize, Test._zHalfSize));
		//MovePointのAABB
		AABB PointAABB = AABB(_MovePoint, 1, 1, 1);
		if (HitTest::AABB_AABB_NOT_EQUAL(TestAABB,PointAABB))
		{
			return true;
		}
		return false;
	}

	//ターゲットのセルを検索する
	bool EnemyBehavior::Search(const Vec3& TargetPos)
	{
		auto MapPtr = dynamic_pointer_cast<EnemyBase>(GetGameObject())->GetCellMap().lock();
		if (MapPtr) {
			auto PathPtr = GetGameObject()->GetComponent<PathSearch>();
			_CellPath.clear();
			//パス検索をかける
			if (PathPtr->SearchCell(TargetPos, _CellPath)) {
				//検索が成功した
				_CellIndex = 0;
				_TargetCellIndex = (int)(_CellPath.size() - 1);
				if (_CellIndex == _TargetCellIndex) {
					//すでに同じセルにいる
					_NextCellIndex = _CellIndex;
				}
				else {
					//離れている
					_NextCellIndex = _CellIndex + 1;

				}
				return true;
			}
			else {
				//失敗した
				_CellIndex = -1;
				_NextCellIndex = -1;
				_TargetCellIndex = -1;
			}
		}
		return false;
	}

	//---------------------------------------------------
	//
	//---------------------------------------------------
	//TO
	void EventCameraBehavior::ToEventPointParam()
	{
		auto ECObj = dynamic_pointer_cast<EventCameraMan>(GetGameObject());
		if (ECObj)
		{
			auto TargetObj = ECObj->GetTargetObject().lock();
			if (TargetObj)
			{
				//開始
				_StartEyePos = GetStage()->GetView()->GetTargetCamera()->GetEye();
				_StartAtPos = GetStage()->GetView()->GetTargetCamera()->GetAt();
				//終了
				//_EndEyePos = 
				_EndAtPos = TargetObj->GetComponent<Transform>()->GetPosition();
				_EndEyePos = _EndAtPos;
				_EndEyePos += (_StartEyePos - _StartAtPos)*2.0f;
				_CurrntTime = 0.0f;
			}
		}
		dynamic_pointer_cast<TestStage>(GameManager::GetManager()->GetTargetStage())->ToEventCamera();
	}

	//TO
	void EventCameraBehavior::ToStartPointParam()
	{
		//終了
		auto CEye = _EndEyePos;
		auto CAt = _EndAtPos;
		auto Camera = dynamic_pointer_cast<TestStage>(GameManager::GetManager()->GetTargetStage())->GetMyCamera();
		//開始
		_EndEyePos = Camera->GetEye();
		_EndAtPos = Camera->GetAt();

		_StartEyePos = CEye;
		_StartAtPos = CAt;
		
		_CurrntTime = 0.0f;
	}

	bool EventCameraBehavior::Execute(float TotalTime)
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		_CurrntTime += ElapsedTime;
		if (_CurrntTime > TotalTime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, _StartEyePos, _EndEyePos, _CurrntTime, TotalTime);
		_AtPos = easing.EaseInOut(EasingType::Cubic, _StartAtPos, _EndAtPos, _CurrntTime, TotalTime);
		auto ptrTrans = GetGameObject()->GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);

		auto ptrEVC = dynamic_pointer_cast<EventCameraMan>(GetGameObject());
		ptrEVC->SetAtPos(_AtPos);
		return false;
	}

	//bool EventCameraBehavior::NextPoint()
	//{

	//}

	//void EventCameraBehavior::RevertParam()
	//{

	//}

}

//end basecross

