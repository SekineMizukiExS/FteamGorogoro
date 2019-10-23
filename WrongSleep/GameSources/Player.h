/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {

	public:
		//構築と破棄
//--------------------------------------------------------------------------------------
/*!
@brief	コンストラクタ
@param[in]	StagePtr	ステージ
*/
//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);

		//初期化
		virtual void OnCreate() override;
		//更新
		//virtual void OnUpdate() override;
	};

}
//end basecross

