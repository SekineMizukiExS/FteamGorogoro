/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

//定数定義
#define INPUT_CODE_MOVE 0x10
#define INPUT_CODE_ROT 0x20

#define INPUT_CODE_UP 0x01
#define INPUT_CODE_DOWN 0x02
#define INPUT_CODE_RIGHT 0x04
#define INPUT_CODE_LEFT 0x08

namespace basecross {
	//-----------------------------------------------------------------------------------
	///Area用の行動クラス
	//-----------------------------------------------------------------------------------
	class AreaBehavior :public Behavior
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@briefコンストラクタ
		@param[in] GameObject ゲームオブジェクト
		!*/
		//--------------------------------------------------------------------------------------
		AreaBehavior(const shared_ptr<GameObject>&GameObjectPtr)
			:Behavior(GameObjectPtr)
		{}
		void SetInputCode(const int& CODE);

	private:
		void Move();
		void Rot();

		bool _moveb = false, _rotb = false;
		float _ptime = 0.0f,_rtime = 0.0f;
	};

}

//end basecross

