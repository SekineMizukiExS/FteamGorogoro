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
		void OnUpdate()override;

	private:
		float _timef;
		int _cnt;
		const float PALSE = 1.0f;
	};
}