/*!
@file Futon.cpp
@brief �z�c�N���X�̎���
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
		@brief ���b�V���ό`�p�֐�
		@return �Ȃ�
		@paramf[in]�U���A�g���A����
		*/
		//-----------------------------------------------------------
		void MeshDeform(float amplitude, float period, float wavelength);;

		void OnEvent(const shared_ptr<Event>& event);
	private:
		float _timef;
		int _cnt;
		const float PALSE = 2.0f;
	};
}