#pragma once
#include "stdafx.h"

namespace basecross {
	
	//-----------------------------------------
	//�Q�[���}�l�[�W���[�N���X����(�V���O���g��)�\��
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