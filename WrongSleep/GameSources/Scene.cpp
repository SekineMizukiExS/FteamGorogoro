
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			//エフェクトインターフェイス生成
			_EfkInterface = ObjectFactory::Create<EfkInterface>();
			GameManager::CreateManager();
			SetUnionTextures();
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::SetUnionTextures()
	{
		wstring mediaPath;
		App::GetApp()->GetDataDirectory(mediaPath);
		App::GetApp()->RegisterTexture(L"Test_TX", mediaPath + L"Textures/" + L"KB.png");
		App::GetApp()->RegisterTexture(L"LeafMat_TX", mediaPath + L"Textures/" + L"leafmat_tx.png");
		App::GetApp()->RegisterTexture(L"LeafMatB_TX", mediaPath + L"Textures/" + L"leafmatBlack_tx.png");
		App::GetApp()->RegisterTexture(L"Player_TX", mediaPath + L"Textures/" + L"Tx_Player.png");
		App::GetApp()->RegisterTexture(L"Player002_TX", mediaPath + L"Textures/" + L"Tx_Player002.png");
		App::GetApp()->RegisterTexture(L"RedApple_TX", mediaPath + L"Textures/" + L"Tx_RedApple.png");
		App::GetApp()->RegisterTexture(L"clearG_TX", mediaPath + L"Textures/" + L"clearGreen.png");
		App::GetApp()->RegisterTexture(L"clearmat_TX", mediaPath + L"Textures/" + L"clearmat.png");
		App::GetApp()->RegisterTexture(L"skybox_TX", mediaPath + L"Textures/" + L"skybox_tx.png");
		App::GetApp()->RegisterTexture(L"Title_TX", mediaPath + L"Textures/" + L"Title.png");

		//モデルテクスチャ
		App::GetApp()->RegisterTexture(L"Button_TX", mediaPath + L"Models/" + L"Tx_Button.png");

		auto modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"MatTest.bmf",true);
		App::GetApp()->RegisterResource(L"MatTest_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"PlayerModel.bmf");
		App::GetApp()->RegisterResource(L"Player_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"Player2.bmf");
		App::GetApp()->RegisterResource(L"Player2_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"Mat.bmf",true);
		App::GetApp()->RegisterResource(L"Mat_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"Apple2.bmf",true);
		App::GetApp()->RegisterResource(L"Apple_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"skyboxObj.bmf", true);
		App::GetApp()->RegisterResource(L"SkyBox_MD", modelMesh);

		modelMesh = MeshResource::CreateBoneModelMesh(mediaPath + L"Models/", L"Button.bmf");
		App::GetApp()->RegisterResource(L"Switch_MD", modelMesh);
		
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"SAModel_bridge.bmf");
		App::GetApp()->RegisterResource(L"Bridge_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"SAModel_Fence.bmf");
		App::GetApp()->RegisterResource(L"Fence_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"SAModel_Flower.bmf");
		App::GetApp()->RegisterResource(L"Flower_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(mediaPath + L"Models/", L"SAModel_WarpPad.bmf");
		App::GetApp()->RegisterResource(L"WarpPad_MD", modelMesh);

		//test
		App::GetApp()->RegisterEffect(L"TestEfk", mediaPath + L"Effects/EnemyHit.efk", _EfkInterface,10);
		//auto multiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(mediaPath + L"MitaGTmodels/", L"ValkylyeModel_TypeC_Valkylye.bmf", true);
		//App::GetApp()->RegisterResource(L"MITAGTV_MD", multiModelMesh);

		//auto multiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(mediaPath + L"Models/", L"Player2_Motion.bmf", true);
		//App::GetApp()->RegisterResource(L"Player3_MD", multiModelMesh);

		App::GetApp()->RegisterEffect(L"Splash_EF", mediaPath + L"Effect/" + L"splash_efk.efk",_EfkInterface,10.0f);
		App::GetApp()->RegisterEffect(L"SideSplash_EF", mediaPath + L"Effect/" + L"sidesplash.efk", _EfkInterface, 1.0f);
	}

	Scene::~Scene() {
	}

	void Scene::OnUpdate()
	{
		//GameManager::GetManager()->OnUpdate();
		SceneBase::OnUpdate();
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {

		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToGameStage")
		{
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTestStage")
		{
			//TestStage
			ResetActiveStage<TestStage>();
		}
		else if (event->m_MsgStr == L"ToMovieStage")
		{
			ResetActiveStage<MyMovieStage>();
		}

		GameManager::GetManager()->SetTargetStage(GetActiveStage());
	}
}
//end basecross
