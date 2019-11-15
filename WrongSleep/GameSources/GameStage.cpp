/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, 5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}


	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePlayer();
		}
		catch (...) {
			throw;
		}
	}

	//--------------------------------------------------------------------------------------
	//	StartStageクラス実体
	//--------------------------------------------------------------------------------------
	void StartStage::CreateViewLight()
	{
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void StartStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
	}

	void StartStage::OnUpdate()
	{
		auto Dev = App::GetApp()->GetInputDevice().GetKeyState();
		if (Dev.m_bLastKeyTbl['S'])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTestStage");
		}
	}

	//!endStartStage

	//--------------------------------------------------------------------------------------
	//	TestStageクラス実体
	//--------------------------------------------------------------------------------------
	void TestStage::CreateViewLight() {
		const Vec3 eye[7] = { Vec3(0.0f, 5.0f, -5.0f),//標準位置
							  Vec3(0.0f, 0.0f, -30.0f),
							  Vec3(0.0f, 20.0f, 00.1f),
							  Vec3(0.0f, 25.0f, -25.0f),
							  Vec3(0.0f,15.0f,10.0f),
							  Vec3(10.0f, 0.0f, -10.0f), 
								Vec3(0.0f,15.0f,-10.0f)};
		const Vec3 at(0.0f);
		//viewポート設定
		Viewport Main, Sub;
		Main.TopLeftX = 0;
		Main.TopLeftY = 0;
		Main.Width = (float)App::GetApp()->GetGameWidth();
		Main.Height = (float)App::GetApp()->GetGameHeight();
		Main.MaxDepth = 1.0f;
		Main.MinDepth = 0.0f;

		Sub.TopLeftX = 1000;
		Sub.TopLeftY = 700;
		Sub.Width = 280;
		Sub.Height = 100;
		Sub.MaxDepth = 1.0f;
		Sub.MinDepth = 0.0f;

		_MView = CreateView <MultiView> ();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		_MView->AddView(Main,PtrCamera);
		PtrCamera->SetEye(eye[3]);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

		auto SubCamera = ObjectFactory::Create<Camera>();
		_MView->AddView(Sub, SubCamera);
		SubCamera->SetEye(eye[1]);
		SubCamera->SetAt(at);

	}

	void TestStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}
//ボックスの作成
	void TestStage::CreateTilingFixedBox() {
		vector< vector<Vec3> > vec = {
			{
			Vec3(50.0f, 1.0f, 50.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f,0.5f,19.5f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f,0.5f,-19.5f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f,XM_PIDIV2,0.0f),
			Vec3(19.5f,0.5f,0.0f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f,XM_PIDIV2,0.0f),
			Vec3(-19.5f,0.5f,0.0f)
			},
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<TilingFixedBox>(v[0], v[1], v[2], 1.0f, 1.0f);
		}
	}

	//固定のボックスの作成
	void TestStage::CreateFixedBox() {
		//配列の初期化
		vector< vector<Vec3> > vec = {
			//{
			//	Vec3(50.0f, 1.0f, 50.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -0.5f, 0.0f)
			//},
			{
				Vec3(5.0f, 0.5f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(10.0f, 0.25f, 10.0f)
			},
			{
				Vec3(5.0f, 0.5f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(15.0f, 0.25f, 10.0f)
			},

			{
				Vec3(2.0f, 1.0f, 2.0f),
				Vec3(0, 0, 0),
				Vec3(10.0f, 0.5f, 10.0f)
			},
			{
				Vec3(4.0f, 1.0f, 4.0f),
				Vec3(0, 0, 0),
				Vec3(-10.0f, 0.5f, 10.0f)
			},
			{
				Vec3(10.0f, 0.5f, 10.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.25f, 10.0f)
			},
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<FixedBox>(v[0], v[1], v[2]);
		}
	}
	void TestStage::CreateStageObject()
	{
		//ゲームオブジェクトビルダー
		GameObjecttXMLBuilder Builder;
		//ゲームオブジェクトの登録
		Builder.Register<StageObjects>(L"FixedObject");
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XMLからゲームオブジェクトの構築
		wstring XMLStr = DataDir+L"ObjectData/" + L"TestStage";
		XMLStr += L".xml";
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/st/objects/Object");
	}

	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			SetPhysicsActive(true);
			CreateViewLight();
			//CreateFixedBox();
			//CreateTilingFixedBox();
			CreatePlayer();
			CreateStageObject();
			AddGameObject<GameManager>();
			 _Ts= AddGameObject<Futon>();
		}
		catch (...) {
			throw;
		}
	}


	void TestStage::OnUpdate()
	{
		auto Dev = App::GetApp()->GetInputDevice().GetKeyState();
		if (Dev.m_bLastKeyTbl['S'])
		{
			PostEvent(1.0f, GetThis<ObjectInterface>(), _Ts, L"StopFuton");
		}
		if (Dev.m_bLastKeyTbl['W'])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), _Ts, L"StartFuton");
		}

	}
}
//end basecross
