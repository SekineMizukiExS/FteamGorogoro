/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera;

	//--------------------------------------------------------------------------------------
	//	ステージベースクラス（エフェクトの更新・描画）
	//--------------------------------------------------------------------------------------
	enum  SelectCamera
	{
		pMyCamera,
		pEventCamera,
		pOpeningCamera
	};

	class StageBase : public Stage {
		shared_ptr<EfkPlay> m_EfkPlay[50];
		int m_EfkCount = 0;

	public:
		//構築と破棄
		StageBase() :Stage(), _MView(nullptr), _MyCameraIndex(NULL), _SubCametaIndex(NULL){}
		virtual ~StageBase() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//描画
		void OnDraw()override;

		void OnDestroy()override;

		SelectCamera GetCameraSelects()const {
			return _Camera;
		}

		shared_ptr<MyCamera>GetMyCamera()const
		{
			return dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		}

		void Effectplay(wstring Key, Vec3 hitpoint);
	protected:
		//ビューの作成
		virtual void CreateViewLight() = 0;

		shared_ptr<MultiView>_MView;
		shared_ptr<SingleView>_EventView;
		shared_ptr<SingleView>_OpeningView;
		//
		size_t _MyCameraIndex;
		size_t _SubCametaIndex;
		SelectCamera _Camera;

	};
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//プレイヤーの作成
		void CreatePlayer();

	public:
		//構築と破棄
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}
		//初期化
		virtual void OnCreate()override;

		void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//TitleStageクラス
	//--------------------------------------------------------------------------------------
	class TitleStage :public Stage
	{
		//ビューの作成
		void CreateViewLight();
		float time = 0;

		bool IsSelect = false;

	public:
		//構築と破棄
		TitleStage():Stage(){}
		virtual ~TitleStage(){}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//LoadStageクラス（読み込むステージ）
	//--------------------------------------------------------------------------------------
	class LoadStage : public StageBase {
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateLoadSprite();
		////リソースロード用のスレッド（スタティック関数）
		//static void LoadResourceFunc();
		////リソースを読み込んだことを知らせるフラグ（スタティック変数）
		//static bool m_Loaded;
		////ミューテックス
		//static std::mutex mtx;
	public:
		//構築と破棄
		LoadStage() :StageBase() {}
		virtual ~LoadStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//SelectStageクラス（未定）
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//MainGameStageクラス
	//--------------------------------------------------------------------------------------
	class MainGameStage :public StageBase
	{
		shared_ptr<SoundItem> m_CurrntBGM;

		void CreateViewLight()override;

		//プレイヤーの作成
		void CreatePlayer();

		void SettingObject();

		void SetMapCost();
	public:
		//構築と破棄
		MainGameStage();
		~MainGameStage();
		//初期化
		void OnCreate()override;
		//更新
		void OnUpdate()override;
		//描画
		void OnDraw()override;
		//破棄
		void OnDestroy()override;

		bool Test = false;

		void ToMyCamera();

		void ToEventCamera();

		void ToOpeningCamera();

	};
	//--------------------------------------------------------------------------------------
	//Movieクラス
	//--------------------------------------------------------------------------------------
	class MyMovieStage :public MovieStage
	{
	public:
		//構築と破棄
		MyMovieStage() :MovieStage() {}
		virtual ~MyMovieStage() {}
		//初期化
		virtual void OnCreate()override;
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

		//void SetCellMapCost();
	public:
		//構築と破棄
		TestStage() :StageBase() {}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		void ToMyCamera();

		void ToEventCamera();

	};
}
//end basecross

