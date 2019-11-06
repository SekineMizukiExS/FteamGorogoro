#pragma once
#include "stdafx.h"

namespace basecross {

	class GameManager final:public GameObject
	{
	public:
		GameManager(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr)
		{
		}

		void OnCreate()override;
		void OnUpdate()override;

	private:
		void DebugLine();
	};

}