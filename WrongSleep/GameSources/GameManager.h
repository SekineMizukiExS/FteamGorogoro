#pragma once
#include "stdafx.h"

namespace basecross {
	
	//前方定義
	class EnemyManager;
	//-----------------------------------------
	//ゲームマネージャークラス実装
	//-----------------------------------------
	class GameManager final:public ObjectInterface
	{
		// デリーター
		struct GMDeleter
		{
			void operator()(GameManager *p) { delete p; }
		};
		static unique_ptr<GameManager, GMDeleter> m_Ins;		///< Singletonで利用する自分自身のポインタ

		explicit GameManager(const shared_ptr<StageBase>&StagePtr);

		~GameManager(){}

		shared_ptr<GameObject> _DebugObj;

		shared_ptr<StageBase> _TargetStage;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief シングルトン構築とアクセサ（構築時はすべてのパラメータを設定する）
		@return	Managerのunique_ptr
		*/
		//--------------------------------------------------------------------------------------
		static unique_ptr<GameManager, GMDeleter>& CreateManager(const shared_ptr<StageBase>&StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief シングルトンアクセサ
		@return	Managerのunique_ptr
		*/
		//--------------------------------------------------------------------------------------
		static unique_ptr<GameManager, GMDeleter>& GetManager();
		//--------------------------------------------------------------------------------------
		/*!
		@brief Managerが作成されてるかチェック
		@return	作成されていればtrue
		*/
		//--------------------------------------------------------------------------------------
		static bool MakeCheck();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 強制破棄
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		static void DeleteManager();

		void OnCreate()override;

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
		//		
		shared_ptr<EnemyManager> _EnemyManager;
		//コピー禁止
		GameManager(const GameManager&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		//ムーブ禁止
		GameManager(const GameManager&&) = delete;
		GameManager& operator=(const GameManager&&) = delete;

	};

	
	class DebugObj :public GameObject
	{
	public:
		DebugObj(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr)
		{
		}

		void OnCreate()override;
		void OnUpdate()override;
	};

}