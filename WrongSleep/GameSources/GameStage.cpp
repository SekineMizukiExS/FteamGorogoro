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
		PtrMultiLight->SetDefaultLighting2();
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
							  Vec3(0.0f, 25.0f, -50.0f),
							  Vec3(0.0f,15.0f,50.0f),
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
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		_MView->AddView(Main,PtrCamera);
		PtrCamera->SetEye(eye[4]);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
		//プレイヤーの情報を渡す
		auto ptrPlayer = GetSharedGameObject<PlayerMarker>(L"PlayerMarker");
		PtrCamera->SetTargetObject(ptrPlayer);
		PtrCamera->SetMinArm(1.0f);
		PtrCamera->SetMaxArm(20.0f);

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

		auto ptrPlayerMarker = AddGameObject<PlayerMarker>();
		ptrPlayerMarker->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerMarker", ptrPlayerMarker);
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


	void TestStage::CreateCMeshBox() {
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
			AddGameObject<CMeshBox>(v[0], v[1], v[2], L"RedApple_TX", L"Apple_MD");
		}
	}

	void TestStage::CreateCommonBox() {
		vector< vector<Vec3> > vec = {
			//{
			//	Vec3(50.0f, 1.0f, 50.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -0.5f, 0.0f)
			//},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(10.0f, 0.5f, 3.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(15.0f, 0.5f, 2.0f)
			},

			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(10.0f, 0.5f, 1.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(-10.0f, 0.5f, -5.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.5f, -3.0f)
			},
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<CommonBox>(v[0],v[1], v[2], L"LeafMatB_TX", L"Apple_MD");
		}
	}

	void TestStage::CreateStageObject()
	{
		//ゲームオブジェクトビルダー
		GameObjecttXMLBuilder Builder;
		//ゲームオブジェクトの登録
		Builder.Register<StageObjects>(L"FixedObject");
		Builder.Register<ToyGuards>(L"Test");
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XMLからゲームオブジェクトの構築
		wstring XMLStr = DataDir+L"ObjectData/" + L"TestStageVer2";
		XMLStr += L".xml";
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage/StageObjects/Object");
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage/EnemyDatas/EnemyData");
	}

	//void TestStage::ToMyCamera() {
	//	auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
	//	//MyCameraに変更
	//	auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
	//	if (ptrMyCamera) {
	//		ptrMyCamera->SetTargetObject(ptrPlayer);
	//		//m_MyCameraViewを使う
	//		//SetView(m_MyCameraView);
	//		//m_CameraSelect = CameraSelect::myCamera;

	//	}
	//}

	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			SetPhysicsActive(true);
			AddGameObject<GameManager>();
			CreatePlayer();
			CreateViewLight();
			//CreateFixedBox();
			//CreateTilingFixedBox();
			//CreateCMeshBox();
			//CreateTilingFixedBox();
			//CreateCommonBox();
			float PieceSize = 3.0f;
			UINT mapSizeUint = 35;
			auto Ptr = AddGameObject<StageCellMap>(Vec3(-50.0f, 0.0f, -50.0f), PieceSize, mapSizeUint, mapSizeUint);
			Ptr->SetDrawActive(true);

			EnemyBase::SetCellMap(Ptr);

			CreateStageObject();
			

			//スカイボックス作成
			//AddGameObject<CMeshBox>(Vec3(10,10,10), Vec3(0,0,0), Vec3(0,0,0), L"skybox_TX", L"SkyBox_MD");

			//AddGameObject<CBoneMeshBox>(Vec3(1, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 0),L"MITAGTV_MD");

			//_Ts= AddGameObject<Futon>();
			//AddGameObject<Futon>();
			//Test
			//GameObjecttXMLBuilder Builder;
			////ゲームオブジェクトの登録
			//Builder.Register<ToyGuards>(L"Test");
			//wstring DataDir;
			//App::GetApp()->GetDataDirectory(DataDir);
			////XMLからゲームオブジェクトの構築
			//wstring XMLStr = DataDir + L"ObjectData/" + L"TestEnemy";
			//XMLStr += L".xml";
			//shared_ptr<EnemyManager> test;
			//Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage1/InitObject/GameObject");			 

			//ToMyCamera();
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
