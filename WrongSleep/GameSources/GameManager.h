#pragma once
#include "stdafx.h"

namespace basecross {
	
	//前方定義
	class EnemyManager;

	//ステージタイプ(データロード時に使用）
	enum class StageType
	{
		TitleStage,
		SelectStage,
		LoadStage,
		GameStage,
	};

	//-----------------------------------------
	//ゲームマネージャークラス実装(ステージが切り替わる度にリセット)
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

		map<wstring,shared_ptr<BaseResource>> _ResMap;		///<-ステージ独自で使用するリソース 

		std::mutex _mutex;										///<-マルチスレッド用
		bool _LoadEnd = false;									///<<-ロード終了したらTrue

	public:
		//static関数
		//--------------------------------------------------------------------------------------
		/*!
		@brief シングルトン構築とアクセサ（構築時はすべてのパラメータを設定する）
		@param[in]　StagePtr　ターゲットステージ(デフォルトでnullptr)
		@return	Managerのunique_ptr
		*/
		//--------------------------------------------------------------------------------------
		static unique_ptr<GameManager, GMDeleter>& CreateManager(const shared_ptr<StageBase>&StagePtr = nullptr);
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
		//!static
		//--------------------------------------------------------------------------------------
		/*!
		@brief 進行度の保存
		@param 
		@return
		@info 
			どれくらい進んだか外部データに保存します。
			ステージを中断したとき保存を実行する。
			チェックポイントを通過したら保存を実行する。
			希望：別スレッドで実行し、終了したらTrue
		*/
		//--------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------
		/*!
		@brief 強制破棄
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void LoadStart(const StageType type);

		void OnCreate()override;

		void OnEvent(const shared_ptr<Event>&event)override;

		//void OnUpdate();

		//ゲッター
		shared_ptr<EnemyManager> GetEnemyManager()const
		{
			return _EnemyManager;
		}
		
		//リソースの読込が終わったらTrue	
		bool GetLoadEnd()const
		{
			return _LoadEnd;
		}

		//セッター
		void SetEnemyManager(shared_ptr<EnemyManager> &EnemyM)
		{
			_EnemyManager = EnemyM;
		}

		void ChangeEventCamera();

		friend EnemyManager;
		
	private:
		//--------------------------------------------------------------------------------------
		/*!
		@brief リソースの読込
		@param[in]	セレクトステージ
		*/
		//--------------------------------------------------------------------------------------
		void LoadResource(const StageType type);

		//Tex
		void TextureLoad(const wstring& Key, const wstring& TextureFileName, const wstring& TexType = L"WIC")
		{
			auto Res = App::GetApp()->RegisterTexture(Key, TextureFileName, TexType);
			_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//wav
		void AudioLoad(const wstring& Key, const wstring& WavFileName)
		{
			auto Res = App::GetApp()->RegisterWav(Key, WavFileName);
			_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//Effect
		void EffectLoad(const wstring& Key, const wstring& EfkFileName, float magnification)
		{
			auto EfkInter = App::GetApp()->GetScene<Scene>()->GetEfkInterface();
			auto Res = App::GetApp()->RegisterEffect(Key, EfkFileName, EfkInter, magnification);
			_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}
		//		
		shared_ptr<EnemyManager> _EnemyManager;
	};

	//GameManagerState
	//データロード中
	class DataLoadState :public ObjState<GameManager>
	{
		DECLARE_SINGLETON_INSTANCE(DataLoadState)
	public:
		void Enter(const shared_ptr<GameManager>&obj)override;
		void Execute(const shared_ptr<GameManager>&obj)override;
		void Exit(const shared_ptr<GameManager>&obj)override;
	};
	//ゲーム実行中
	class ExecuteGameState :public ObjState<GameManager>
	{
		DECLARE_SINGLETON_INSTANCE(ExecuteGameState)
	public:
		void Enter(const shared_ptr<GameManager>&obj)override;
		void Execute(const shared_ptr<GameManager>&obj)override;
		void Exit(const shared_ptr<GameManager>&obj)override;
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