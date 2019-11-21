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
	//StartStageクラス
	//--------------------------------------------------------------------------------------
	class StartStage :public Stage
	{
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		StartStage():Stage(){}
		virtual ~StartStage(){}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	TestStageクラス
	//--------------------------------------------------------------------------------------
	class Futon;
	class TestStage :public Stage
	{
		//オープニングのボスへのフォーカス用ビュー
		shared_ptr<SingleView> m_MyCameraView;

		//ビューの作成
		void CreateViewLight();
		//プレイヤーの作成
		void CreatePlayer();

		void DebugLine();
		//固定のボックスの作成
		void CreateFixedBox();
		//タイリングボックスの作成
		void CreateTilingFixedBox();
		void CreateStageObject();

		void ToMyCamera();

		shared_ptr<MultiView>_MView;

		shared_ptr<Futon> _Ts;
	public:
		//構築と破棄
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		shared_ptr<MultiView>GetMultiView()const
		{
			return _MView;
		}
	};
}
//end basecross

