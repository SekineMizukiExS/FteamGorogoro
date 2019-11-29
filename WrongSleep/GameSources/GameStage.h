/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージベースクラス（エフェクトの更新・描画）
	//--------------------------------------------------------------------------------------
	class StageBase : public Stage {
		//ビューの作成
		virtual void CreateViewLight() = 0;

	public:
		//構築と破棄
		StageBase() :Stage() {}
		virtual ~StageBase() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//描画
		virtual void OnDraw()override;
	};
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
	class TestStage :public StageBase
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
		//カスタムメッシュボックスの作成
		void CreateCMeshBox();
		void CreateCommonBox();
		void CreateStageObject();

		void ToMyCamera();

		shared_ptr<MultiView>_MView;

		shared_ptr<Futon> _Ts;
	public:
		//構築と破棄
		TestStage() :StageBase() {}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		void OnDraw()override {}

		shared_ptr<MultiView>GetMultiView()const
		{
			return _MView;
		}
	};
}
//end basecross

