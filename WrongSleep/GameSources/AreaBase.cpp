/*!
@file AreaBase.h
@brief �e�X�e�[�W�̃v���C�G���A�̐e�N���X�Ȃ�
*/
#include"stdafx.h"
#include"Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///AI�p�̃X�e�[�g
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
	///2P�p�̃X�e�[�g
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