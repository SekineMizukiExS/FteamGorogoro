#pragma once
#include "stdafx.h"

namespace basecross {
	
	//前方定義
	class EnemyManager;
	struct GameEvent;
	class EventCameraMan;
	class DataBinaryIO;

	//------------------------------------------------------
	//セーブデータ形式
	//------------------------------------------------------
	struct SaveData
	{
		//前回終了時のマップ名
		wstring LastMapName;
		//前回マップの読込時のプレイヤー地点名
		wstring LastLoadBlock;
		//累計プレイ時間
		float CumulativeTime;

		SaveData(){}
		SaveData(const wstring& MapName, const wstring& LoadBlock, const float& Time)
			:LastMapName(MapName), LastLoadBlock(LoadBlock), CumulativeTime(Time)
		{}
	};

	//ゲームイベントタイプ
	/*
	*0標準
	*1ギミック作動
	*2ギミック作動（カメラが動く)
	*3ステージ遷移（ステージデータ読込）
	*4カットシーン（未定）
	*/
	enum class GameEventType
	{
		Default,
		Gimmick,
		GimmickAction,
		MoveStage,
		CutScene,
		SaveDataIO
	};

	class GameEventInterface
	{
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief プロテクトコンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		GameEventInterface() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief プロテクトデストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameEventInterface() {}
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントのSEND（キューに入れずにそのまま送る）
		@param[in]	Sender	イベント送信者（nullptr可）
		@param[in]	ReceiverKey	受け手側オブジェクトを判別するキー
		@param[in]	MsgStr	メッセージ
		@param[in,out] Type イベントタイプ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントのSEND（キューに入れずにそのまま送る）
		@param[in]	Sender	イベント送信者（nullptr可）
		@param[in]	ReceiverKey	受け手側オブジェクトを判別するキー
		@param[in]	MsgStr	メッセージ
		@param[in,out] Type イベントタイプ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SendGameEvent(const shared_ptr<GameEventInterface>& Sender,
			const wstring& MsgStr, const GameEventType Type = GameEventType::MoveStage);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントのSEND（キューに入れずにそのまま送る）
		@param[in]	Sender	イベント送信者（nullptr可）
		@param[in]	Receiver	イベント受信者（nullptr不可）
		@param[in]	MsgStr	メッセージ
		@param[in,out] Type イベントタイプ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントを受け取る
		@param[in]	event	イベント
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnGameEvent(const shared_ptr<GameEvent>& event) {}
	private:
		//コピー禁止
		GameEventInterface(const GameEventInterface&) = delete;
		GameEventInterface& operator=(const GameEventInterface&) = delete;
		//ムーブ禁止
		GameEventInterface(const GameEventInterface&&) = delete;
		GameEventInterface& operator=(const GameEventInterface&&) = delete;

	};

	//-----------------------------------------
	///ゲームイベント構造体
	//-----------------------------------------
	struct GameEvent
	{
		///	このメッセージを送ったオブジェクト
		weak_ptr<GameEventInterface> m_Sender;
		///	受け取るオブジェクト（nullptrの場合はゲームマネージャーもしくはキーワードで識別するオブジェクト）
		weak_ptr<GameEventInterface> m_Receiver;
		///	メッセージ文字列
		wstring m_MsgStr;
		///ゲームイベントタイプ
		GameEventType m_Type;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	DispatchTime	配送までの時間
		@param[in]	Sender	送り側オブジェクト（nullptr可）
		@param[in]	Receiver	受け手側オブジェクト
		@param[in]	MsgStr	メッセージ文字列
		@param[in]	Type イベントタイプ
		*/
		//--------------------------------------------------------------------------------------
		GameEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default) :
			m_Sender(Sender),
			m_Receiver(Receiver),
			m_MsgStr(MsgStr),
			m_Type(Type)
		{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		~GameEvent() {}
	};

	//--------------------------------------------------------------------------------------
	///	イベント配送クラス
	//--------------------------------------------------------------------------------------
	class GameEventDispatcher {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	SceneBasePtr	シーンベースのポインタ
		*/
		//--------------------------------------------------------------------------------------
		explicit GameEventDispatcher();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameEventDispatcher();


		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントを受け取るグループに追加（グループがなければその名前で作成）
		@param[in]	GroupKey	グループ名
		@param[in]	Receiver	受け手側オブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddEventReceiverGroup(const wstring& GroupKey, const shared_ptr<GameEventInterface>& Receiver);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントカメラマンの設定
		@param[in]	Receiver	カメラマンオブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddEventCameraMan(const shared_ptr<EventCameraMan>& Receiver);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントのSEND（キューに入れずにそのまま送る）
		@param[in]	Sender	送り側オブジェクト（nullptr可）
		@param[in]	Receiver	受け手側オブジェクト
		@param[in]	MsgStr	メッセージ文字列
		@param[in]	Info	追加情報をもつユーザーデータ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SendEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントのSEND（キューに入れずにそのまま送る）
		@param[in]	Sender	送り側オブジェクト（nullptr可）
		@param[in]	Receiver	受け手側オブジェクト
		@param[in]	MsgStr	メッセージ文字列
		@param[in]	Info	追加情報をもつユーザーデータ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SendEvent(const shared_ptr<GameEventInterface>& Sender,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	イベントのSEND（キューに入れずにそのまま送る）
		@param[in]	Sender	イベント送信者（nullptr可）
		@param[in]	Receiver	イベント受信者（nullptr不可）
		@param[in]	MsgStr	メッセージ
		@param[in,out]	Info	追加情報
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SendEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
	private:
		//--------------------------------------------------------------------------------------
		/*!
		@brief Typeごとの処理分け
		@param[in]	
		@return	bool
		*/
		//--------------------------------------------------------------------------------------
		void TypeEvent(const shared_ptr<GameEvent>& gameevent);
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
		//コピー禁止
		GameEventDispatcher(const GameEventDispatcher&) = delete;
		GameEventDispatcher& operator=(const GameEventDispatcher&) = delete;
		//ムーブ禁止
		GameEventDispatcher(const GameEventDispatcher&&) = delete;
		GameEventDispatcher& operator=(const GameEventDispatcher&&) = delete;
	};


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
	class GameManager :public ObjectInterface
	{
		// デリーター
		struct GMDeleter
		{
			void operator()(GameManager *p) { delete p; }
		};
		static unique_ptr<GameManager, GMDeleter> m_Ins;		///< Singletonで利用する自分自身のポインタ

		explicit GameManager();

		~GameManager(){}

		shared_ptr<GameObject> _DebugObj;

		shared_ptr<Stage> _TargetStage;

		map<wstring,shared_ptr<BaseResource>> _ResMap;		///<-ステージ独自で使用するリソース 
		shared_ptr<GameEventDispatcher> m_GameEventDispatcher;	///< イベント送信オブジェクト

		shared_ptr<DataBinaryIO> m_DataIO;

		map<wstring, Vec3> _SettingPosData; ///<-初期配置データ群

		int MaxKeyNums;						///<-クリアに必要な鍵数

		int m_CurrntKeyNums;

		int MaxMoveCount;					///<-ステージ上で移動できる回数

		wstring _CurrntSaveDataPath;

		wstring _XMLFileName;

		wstring _LoadPosKey;

		float _CumulativeTime; ///<-累計プレイ時間

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
		static unique_ptr<GameManager, GMDeleter>& CreateManager();
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
		void SaveGameData();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージの配置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------
		/*!
		@brief 強制破棄
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void LoadStart();

		void OnCreate()override;

		void OnUpdate();

		void OnEvent(const shared_ptr<Event>&event)override;

		//void OnGameEvent(const shared_ptr<GameEvent>&gameevent);

		//void OnUpdate();

		//ゲッター
		shared_ptr<EnemyManager> GetEnemyManager()const
		{
			return _EnemyManager;
		}
		
		const wstring GetXMLFilePath()const { return _XMLFileName; }

		const wstring GetLoadPosKey()const { return _LoadPosKey; }

		const float &GetCumulativeTime()const { return _CumulativeTime; }

		const int &GetMaxMoveCount()const { return MaxMoveCount; }

		shared_ptr<GameEventDispatcher> GetGameEventDispatcher()const { return m_GameEventDispatcher; }

		shared_ptr<DataBinaryIO> GetDataIO()const { return m_DataIO; }

		const shared_ptr<Stage> GetTargetStage()const { return _TargetStage; }

		const Vec3 GetSettingPosData(const wstring& PosKey) { return _SettingPosData[PosKey]; }

		//鍵数
		const bool CheckKeyVol() { return MaxKeyNums <= m_CurrntKeyNums; }

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

		void SetTargetStage(const shared_ptr<Stage> &stage)
		{
			_TargetStage = stage;
		}

		void SetXMLFilePath(const wstring &FilePath)
		{
			_XMLFileName = FilePath;
		}

		void SetLoadPosKey(const wstring &PosKey)
		{
			_LoadPosKey = PosKey;
		}

		void AddKeyNums(const int &Vol)
		{
			m_CurrntKeyNums += Vol;
		}

		void SetSaveData(const SaveData& SaveDataPtr,const wstring DataPath)
		{
			_CurrntSaveDataPath = DataPath;
			_XMLFileName = SaveDataPtr.LastMapName;
			_LoadPosKey = SaveDataPtr.LastLoadBlock;
			_CumulativeTime = SaveDataPtr.CumulativeTime;
		}

		void SetSettingPosData(const wstring& FilePath);

		void MovedPlayer() 
		{
			MaxMoveCount--;
			if (MaxMoveCount <= 0)
			{
				PostEvent(0.0f, nullptr, App::GetApp()->GetScene<Scene>(), L"ToMainGameStage");
			}
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
		void LoadResource();

		//Tex
		void TextureLoad(const wstring& Key, const wstring& TextureFileName, const wstring& TexType = L"WIC")
		{
			auto Res = App::GetApp()->RegisterTexture(Key, TextureFileName, TexType);
			//_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//wav
		void AudioLoad(const wstring& Key, const wstring& WavFileName)
		{
			auto Res = App::GetApp()->RegisterWav(Key, WavFileName);
			//_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//Effect
		void EffectLoad(const wstring& Key, const wstring& EfkFileName, float magnification)
		{
			auto EfkInter = App::GetApp()->GetScene<Scene>()->GetEfkInterface();
			auto Res = App::GetApp()->RegisterEffect(Key, EfkFileName, EfkInter, magnification);
			//_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
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