/*!
@file AreaBase.h
@brief 各ステージのプレイエリアの親クラスなど
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