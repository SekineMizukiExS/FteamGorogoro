#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//static�ϐ�����
	unique_ptr<GameManager, GameManager::GMDeleter> GameManager::m_Ins;
	//�\�z�Ɣj��
	GameManager::GameManager(const shared_ptr<StageBase>&StagePtr)
		:_TargetStage(StagePtr)
	{
		_EnemyManager = make_shared<EnemyManager>();
	}


	//�V���O���g���\�z
	unique_ptr<GameManager, GameManager::GMDeleter>& GameManager::CreateManager(const shared_ptr<StageBase>&StagePtr) {
		try {
			if (m_Ins.get() == 0) {
				//�������g�̍\�z
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

	//�V���O���g���A�N�Z�T
	unique_ptr < GameManager, GameManager::GMDeleter > & GameManager::GetManager() {
		try {
			if (m_Ins.get() == 0) {
				throw BaseException(
					L"�}�l�[�W���[���܂��쐬����Ă܂���",
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

	//�����j��
	void GameManager::DeleteManager() {
		if (m_Ins.get()) {
			m_Ins.reset();
		}
	}


	void GameManager::OnCreate()
	{
		_TargetStage->AddGameObject<DebugObj>();
	}



	//-----------------------------------------------------------

	void DebugObj::OnCreate()
	{
		//Debug
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 50.0f, 640.0f, 480.0f));

		//�e�p�t�H�[�}���X�𓾂�
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

		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);


	}
}