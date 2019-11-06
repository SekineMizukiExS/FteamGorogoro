/*!
@file Futon.cpp
@brief 布団クラスの実装
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
		//-----------------------------------------------------------
		/*!
		@brief メッシュ変形用関数
		@return なし
		@paramf[in]振幅、波長、周期
		*/
		//-----------------------------------------------------------
		void MeshDeform(float amplitude, float period, float wavelength);;
	private:
		float _timef;
		int _cnt;
		const float PALSE = 1.0f;
	};
}