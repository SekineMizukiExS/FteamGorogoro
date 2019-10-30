/*!
@file AreaBase.h
@brief �e�X�e�[�W�̃v���C�G���A�̐e�N���X�Ȃ�
*/
#pragma once
#include "stdafx.h"

namespace basecross {


	class AreaBase : public GameObject {
	public:
		AreaBase(const shared_ptr<Stage>&stage)
			:GameObject(stage)
		{}

	protected:
		float m_RotObj;
		unique_ptr<StateMachine<AreaBase>> m_State;
	private:

	};

	//--------------------------------------------------------------------------------------
	///AI�p�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	class SelectAIState :public ObjState<AreaBase>
	{
		SelectAIState(){}
	public:
		DECLARE_SINGLETON_INSTANCE(SelectAIState)
		virtual void Enter(const shared_ptr<AreaBase>&Obj)override;
		virtual void Execute(const shared_ptr<AreaBase>&Obj)override;
		virtual void Exit(const shared_ptr<AreaBase>&Obj)override;
	};
	//--------------------------------------------------------------------------------------
	///2P�p�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	class Select2PState :public ObjState<AreaBase>
	{
		Select2PState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(Select2PState)
		virtual void Enter(const shared_ptr<AreaBase>&Obj)override;
		virtual void Execute(const shared_ptr<AreaBase>&Obj)override;
		virtual void Exit(const shared_ptr<AreaBase>&Obj)override;
	};


}