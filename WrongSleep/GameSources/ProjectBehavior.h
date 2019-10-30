/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

//�萔��`
#define INPUT_CODE_MOVE 0x10
#define INPUT_CODE_ROT 0x20

#define INPUT_CODE_UP 0x01
#define INPUT_CODE_DOWN 0x02
#define INPUT_CODE_RIGHT 0x04
#define INPUT_CODE_LEFT 0x08

namespace basecross {
	//-----------------------------------------------------------------------------------
	///Area�p�̍s���N���X
	//-----------------------------------------------------------------------------------
	class AreaBehavior :public Behavior
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief�R���X�g���N�^
		@param[in] GameObject �Q�[���I�u�W�F�N�g
		!*/
		//--------------------------------------------------------------------------------------
		AreaBehavior(const shared_ptr<GameObject>&GameObjectPtr)
			:Behavior(GameObjectPtr)
		{}
		void SetInputCode(const int& CODE);

	private:
		enum class SwitchIO
		{
			Stop,
			Excute
		};

		void Move();
		void Rot();

		void CheckQuat(float CheckVal);
		//float ExeTime(float nowtime);

		bool _moveb = false, _rotb = false;
		float _ptime = 0.0f,_rtime = 0.0f;
		float _rotval = 0.0f;

		const float _MaxQuat = XM_PIDIV4;
		SwitchIO _rotsw = SwitchIO::Excute;

	};

}

//end basecross

