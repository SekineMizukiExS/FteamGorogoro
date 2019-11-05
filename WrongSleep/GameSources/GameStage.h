/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//プレイヤーの作成
		void CreatePlayer();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
	};

	//--------------------------------------------------------------------------------------
	//	TestStageクラス
	//--------------------------------------------------------------------------------------
	class TestStage :public Stage
	{
		//ビューの作成
		void CreateViewLight();
		//プレイヤーの作成
		void CreatePlayer();

		void DebugLine();
	public:
		//構築と破棄
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;
	};
}
//end basecross

