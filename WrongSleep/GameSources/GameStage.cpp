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
							  Vec3(0.0f, 0.0f, -5.0f),
							  Vec3(0.0f, 20.0f, 0.1f),
							  Vec3(50.0f, 50.0f, -50.0f),
							  Vec3(0.0f,15.0f,10.0f),
							  Vec3(10.0f, 0.0f, -10.0f),
							  Vec3(15.0f, 0.0f,-10.0f)};
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
		SubCamera->SetEye(eye[2]);
		SubCamera->SetAt(at);

	}

	void TestStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	void TestStage::CreateStageObject()
	{
		//ゲームオブジェクトビルダー
		GameObjecttXMLBuilder Builder;
		//ゲームオブジェクトの登録
		Builder.Register<FixedObject>(L"FixedObject");
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XMLからゲームオブジェクトの構築
		wstring XMLStr = DataDir+L"ObjectData/" + L"GameStageObject";
		XMLStr += L".xml";
		Builder.Build(GetThis<Stage>(), XMLStr, L"Stage1/GameObject");
	}

	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<GameManager>();
			AddGameObject<Futon>();
			CreatePlayer();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
