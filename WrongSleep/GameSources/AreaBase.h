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

	private:

	};

}