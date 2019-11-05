/*!
@file AreaBase.h
@brief 各ステージのプレイエリアの親クラスなど
*/
#include"stdafx.h"
#include"Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///AI用のステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(SelectAIState)

	void SelectAIState::Enter(const shared_ptr<AreaBase>&Obj)
	{

	}

	void SelectAIState::Execute(const shared_ptr<AreaBase>&Obj)
	{
		Obj->GetBehavior<AreaBehavior>()->SetInputCode(INPUT_CODE_ROT);
		Obj->GetBehavior<AreaBehavior>()->SetInputCode(INPUT_CODE_MOVE);
	}

	void SelectAIState::Exit(const shared_ptr<AreaBase>&Obj)
	{

	}

	//--------------------------------------------------------------------------------------
	///2P用のステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(Select2PState)

	void Select2PState::Enter(const shared_ptr<AreaBase>&Obj)
	{

	}

	void Select2PState::Execute(const shared_ptr<AreaBase>&Obj)
	{

	}

	void Select2PState::Exit(const shared_ptr<AreaBase>&Obj)
	{

	}
}