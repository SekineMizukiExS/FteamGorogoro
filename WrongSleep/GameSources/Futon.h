/*!
@file Futon.cpp
@brief •z’cƒNƒ‰ƒX‚ÌŽÀ‘•
*/
#pragma once
#include"stdafx.h"

namespace basecross
{
	class Futon :public AreaBase
	{
	public:
		Futon(const shared_ptr<Stage>&stage)
			:AreaBase(stage)
		{}

		void OnCreate()override;
	};
}