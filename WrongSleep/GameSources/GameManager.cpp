#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	void GameManager::OnCreate()
	{
		//Debug
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 50.0f, 640.0f, 480.0f));
	}

	void GameManager::OnUpdate()
	{
		DebugLine();
	}

	void GameManager::DebugLine()
	{
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps) + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(FPS);

	}
}