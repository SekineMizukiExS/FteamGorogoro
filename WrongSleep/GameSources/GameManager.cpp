#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//static変数実体
	unique_ptr<GameManager, GameManager::GMDeleter> GameManager::m_Ins;
	//構築と破棄
	GameManager::GameManager(const shared_ptr<StageBase>&StagePtr)
		:_TargetStage(StagePtr)
	{
		_EnemyManager = ObjectFactory::Create<EnemyManager>();
	}


	//シングルトン構築
	unique_ptr<GameManager, GameManager::GMDeleter>& GameManager::CreateManager(const shared_ptr<StageBase>&StagePtr) {
		try {
			if (m_Ins.get() == 0) {
				//自分自身の構築
				m_Ins.reset(new GameManager(StagePtr));
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
		_TargetStage->AddGameObject<DebugObj>();
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