
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
			SetTextures();
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTestStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::SetTextures()
	{
		wstring mediaPath;
		App::GetApp()->GetDataDirectory(mediaPath);
		App::GetApp()->RegisterTexture(L"Test_TX", mediaPath +L"Textures/"+ L"KB.png");

		auto modelMesh = MeshResource::CreateStaticModelMesh(mediaPath+L"Models/",L"MatTest.bmf");
		App::GetApp()->RegisterResource(L"MatTest_MD", modelMesh);

	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTestStage")
		{
			//TestStage
			ResetActiveStage<TestStage>();
		}
	}

}
//end basecross
