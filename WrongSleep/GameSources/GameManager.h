#pragma once
#include "stdafx.h"

namespace basecross {
	
	//前方定義
	class EnemyManager;
	//-----------------------------------------
	//ゲームマネージャークラス実装
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
		//コピー禁止
		GameManager(const GameManager&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		//ムーブ禁止
		GameManager(const GameManager&&) = delete;
		GameManager& operator=(const GameManager&&) = delete;

	};

}