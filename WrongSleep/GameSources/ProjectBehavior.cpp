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
		const float TotalTime = 2.0f;
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		_rtime += ElapsedTime;
		if (TotalTime < _rtime) {
			_rtime = 0;
			_rotb = !_rotb;
			return;
		}
		auto obj = GetGameObject();
		auto TransComp = obj->GetComponent<Transform>();
		const float Rad = XM_1DIV2PI;
		Vec3 Rotation = TransComp->GetRotation();

		Rotation.z += _rotb ? Rad * ElapsedTime : -Rad * ElapsedTime;

		TransComp->SetRotation(Rotation);

	}
}

//end basecross

