#pragma once
#include "stdafx.h"

namespace basecross {
	
	//�O����`
	class EnemyManager;
	//-----------------------------------------
	//�Q�[���}�l�[�W���[�N���X����
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

		shared_ptr<EnemyManager> GetEnemyManager()const
		{
			return _EnemyManager;
		}

		void SetEnemyManager(shared_ptr<EnemyManager> &EnemyM)
		{
			_EnemyManager = EnemyM;
		}

		friend EnemyManager;
	private:
		void DebugLine();
		//
		shared_ptr<EnemyManager> _EnemyManager;
		//�R�s�[�֎~
		GameManager(const GameManager&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		//���[�u�֎~
		GameManager(const GameManager&&) = delete;
		GameManager& operator=(const GameManager&&) = delete;

	};

}