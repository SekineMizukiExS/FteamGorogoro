#pragma once
#include "stdafx.h"

namespace basecross {
	
	//-----------------------------------------
	//ゲームマネージャークラス実装(シングルトン)予定
	//-----------------------------------------
	class GameManager final:public GameObject
	{
	public:
		explicit GameManager(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr)
		{
		}

		void OnCreate()override;
		void OnUpdate()override;

	private:
		void DebugLine();

		unique_ptr<GameManager> _Ins;
	};

}