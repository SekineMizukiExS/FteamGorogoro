
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
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
