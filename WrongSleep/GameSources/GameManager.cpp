#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	///	GameEventインターフェイス
	//--------------------------------------------------------------------------------------
	void GameEventInterface::SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
		const wstring& MsgStr, const GameEventType Type)
	{
		GameManager::GetManager()->GetGameEventDispatcher()->SendEvent(Sender, Receiver, MsgStr, Type);
	}

	void GameEventInterface::SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
		const wstring& MsgStr, const GameEventType Type)
	{
		GameManager::GetManager()->GetGameEventDispatcher()->SendEvent(Sender, ReceiverKey, MsgStr, Type);
	}


	//--------------------------------------------------------------------------------------
	//	struct EventDispatcher::Impl;
	//	用途: Impl構造体
	//--------------------------------------------------------------------------------------
	struct GameEventDispatcher::Impl {
		//イベントのキュー

		map<wstring, vector<weak_ptr<GameEventInterface>>> m_EventInterfaceGroupMap;

		weak_ptr<EventCameraMan> m_EventCameraMan;
		//
		//--------------------------------------------------------------------------------------
		//	void Discharge(
		//	const Event& event	//イベント
		//	);
		//用途: イベントの送信
		//戻り値: なし
		//--------------------------------------------------------------------------------------
		void Discharge(const shared_ptr<GameEvent>& event);
		Impl() {}
		~Impl() {}
	};

	void GameEventDispatcher::Impl::Discharge(const shared_ptr<GameEvent>& event) {
		auto shptr = event->m_Receiver.lock();
		if (shptr) {
			//受け手が有効
			shptr->OnGameEvent(event);
		}
	}



	//--------------------------------------------------------------------------------------
	///	イベント配送クラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	GameEventDispatcher::GameEventDispatcher() :
		pImpl(new Impl())
	{}
	GameEventDispatcher::~GameEventDispatcher() {}

	void GameEventDispatcher::AddEventReceiverGroup(const wstring& GroupKey, const shared_ptr<GameEventInterface>& Receiver) {
		auto it = pImpl->m_EventInterfaceGroupMap.find(GroupKey);
		if (it != pImpl->m_EventInterfaceGroupMap.end()) {
			//キーがあった
			it->second.push_back(Receiver);
		}
		else {
			//グループがない
			vector<weak_ptr<GameEventInterface>> vec;
			pImpl->m_EventInterfaceGroupMap[GroupKey] = vec;
			pImpl->m_EventInterfaceGroupMap[GroupKey].push_back(Receiver);
		}
	}

	void GameEventDispatcher::AddEventCameraMan(const shared_ptr<EventCameraMan>& Receiver)
	{
		auto Obj = pImpl->m_EventCameraMan.lock();
		if (!Obj)
		{
			pImpl->m_EventCameraMan = Receiver;
		}
		return;
	}

	//イベントのSEND（キューに入れずにそのまま送る）
	void GameEventDispatcher::SendEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
		const wstring& MsgStr, const GameEventType Type) {
		//イベントの作成 
		auto Ptr = make_shared<GameEvent>(Sender, Receiver, MsgStr, Type);
		//送信
		TypeEvent(Ptr);
	}

	void GameEventDispatcher::SendEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
		const wstring& MsgStr, const GameEventType Type) {
		//ReceiverKeyによる相手の特定
		//重複キーの検査
		auto it = pImpl->m_EventInterfaceGroupMap.find(ReceiverKey);
		if (it != pImpl->m_EventInterfaceGroupMap.end()) {
			//キーがあった
			for (auto v : it->second) {
				auto shptr = v.lock();
				if (shptr) {
					//イベントの作成 
					auto Ptr = make_shared<GameEvent>(Sender, shptr, MsgStr, Type);
					//イベントの送出
					TypeEvent(Ptr);
				}
			}
		}
		//キーが見つからなくても何もしない
	}

	void GameEventDispatcher::TypeEvent(const shared_ptr<GameEvent>& gameevent)
	{
		auto type = gameevent->m_Type;
		auto ECM = pImpl->m_EventCameraMan.lock();
		auto ER = dynamic_pointer_cast<MovingObject>(gameevent->m_Receiver.lock());

		switch (type)
		{
			//通常イベント
		case basecross::GameEventType::Default:
			pImpl->Discharge(gameevent);
			break;
			//ギミックイベント
		case basecross::GameEventType::Gimmick:
			pImpl->Discharge(gameevent);
			break;
			//カメラ移動ギミックイベント
		case basecross::GameEventType::GimmickAction:
			/*
			*カメラを移動させる
			*移動完了した後イベント飛ばす
			*/
			ECM->SetTargetObject(ER);
			//dynamic_pointer_cast<TestStage>(GameManager::GetManager()->GetTargetStage())->ToEventCamera();
			ECM->SetGameEvent(gameevent);
			ECM->GetStateMachine()->ChangeState(MoveToEventPoint::Instance());
			break;
			//ステージ移動イベント
		case basecross::GameEventType::MoveStage:
			break;
			//カットシーン・イベントシーンイベント
		case basecross::GameEventType::CutScene:
			break;
		default:
			break;
		}
	}

	//-----------------------------------------------------------------
	///GameManagerクラス
	//-----------------------------------------------------------------

	//static変数実体
	unique_ptr<GameManager, GameManager::GMDeleter> GameManager::m_Ins;
	//構築と破棄
	GameManager::GameManager()
		:_TargetStage(nullptr)
	{
		_EnemyManager = ObjectFactory::Create<EnemyManager>();
		m_GameEventDispatcher = make_shared<GameEventDispatcher>();
	}


	//シングルトン構築
	unique_ptr<GameManager, GameManager::GMDeleter>& GameManager::CreateManager() {
		try {
			if (m_Ins.get() == 0) {
				//自分自身の構築
				m_Ins.reset(new GameManager());
				m_Ins->OnPreCreate();
				m_Ins->OnCreate();
			}
			return m_Ins;
		}
		catch (...) {
			throw;
		}
	}

	//シングルトンアクセサ
	unique_ptr < GameManager, GameManager::GMDeleter > & GameManager::GetManager() {
		try {
			if (m_Ins.get() == 0) {
				throw BaseException(
					L"マネージャーがまだ作成されてません",
					L"if (m_Ins.get() == 0)",
					L"GameManager::GetManager()"
				);
			}
			return m_Ins;
		}
		catch (...) {
			throw;
		}

	}

	bool GameManager::MakeCheck() {
		if (m_Ins.get() == 0) {
			return false;
		}
		return true;
	}

	//強制破棄
	void GameManager::DeleteManager() {
		if (m_Ins.get()) {
			m_Ins.reset();
		}
	}

	void GameManager::LoadStart(const StageType type)
	{
		std::thread LoadThread(&GameManager::LoadResource, this, type);
		LoadThread.detach();
	}

	//
	void GameManager::LoadResource(const StageType type)
	{
		_mutex.lock();
		_LoadEnd = false;
		_ResMap.clear();
		_mutex.unlock();

		//メディアパス
		wstring mediaPath;
		App::GetApp()->GetDataDirectory(mediaPath);
		wstring TexturePath = mediaPath + L"Textures/";
		wstring ModelPath = mediaPath + L"Models/";
		wstring EffectPath = mediaPath + L"Effect/";

		switch (type)
		{
		case StageType::TitleStage://タイトルステージで使うデータ
			break;
		case StageType::GameStage:
			break;
		case StageType::LoadStage:
			break;
		case StageType::SelectStage:
			break;
		}

		_mutex.lock();
		_LoadEnd = true;
		_mutex.unlock();
	}
	//
	void GameManager::OnCreate()
	{
		//_TargetStage->AddGameObject<DebugObj>();
	}

	void GameManager::OnEvent(const shared_ptr<Event>&event)
	{
		if (event->m_MsgStr == L"EventStart")
		{
			//auto EventCamera = _TargetStage->GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
			//SendEvent(GetThis<ObjectInterface>(), _TargetStage, L"ChangeCamera");
		}
	}

	void GameManager::ChangeEventCamera()
	{
		
	}

	//-----------------------------------------------------------

	void DebugObj::OnCreate()
	{
		//Debug
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 50.0f, 640.0f, 480.0f));

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}

	void DebugObj::OnUpdate()
	{
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		fpsStr += Util::FloatToWStr(ElapsedTime);
		fpsStr += L"\n";

		wstring updatePerStr(L"UpdatePerformance:\t");
		updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		updatePerStr += L"\tmillisecond\n";

		wstring drawPerStr(L"DrawPerformance:\t");
		drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		drawPerStr += L"\tmillisecond\n";

		wstring collPerStr(L"CollisionPerform:\t");
		collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		collPerStr += L"\tmillisecond\n";

		wstring collMiscStr(L"ColMiscPerform:\t");
		collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		collMiscStr += L"\tmillisecond\n";

		wstring collTernCountStr(L"CollisionCountOfTern:\t");
		collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		collTernCountStr += L"\n";

		wstring ObjCount(L"ObjectCount:\t");
		ObjCount += Util::UintToWStr((UINT)GetStage()->GetGameObjectVec().size());
		ObjCount += L"\n";

		wstring str = fpsStr + updatePerStr + drawPerStr + collPerStr + collMiscStr
			+ collTernCountStr + ObjCount;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);


	}
}