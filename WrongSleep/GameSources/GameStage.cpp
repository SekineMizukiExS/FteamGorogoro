/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}


	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreatePlayer();
		}
		catch (...) {
			throw;
		}
	}


	//--------------------------------------------------------------------------------------
	//	TestStage�N���X����
	//--------------------------------------------------------------------------------------
	void TestStage::CreateViewLight() {
		const Vec3 eye[7] = { Vec3(0.0f, 5.0f, -5.0f),//�W���ʒu
							  Vec3(0.0f, 0.0f, -5.0f),
							  Vec3(0.0f, 20.0f, 0.1f),
							  Vec3(50.0f, 50.0f, -50.0f),
							  Vec3(0.0f,15.0f,10.0f),
							  Vec3(10.0f, 0.0f, -10.0f),
							  Vec3(15.0f, 0.0f,-10.0f)};
		const Vec3 at(0.0f);
		//view�|�[�g�ݒ�
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
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		_MView->AddView(Main,PtrCamera);
		PtrCamera->SetEye(eye[3]);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

		auto SubCamera = ObjectFactory::Create<Camera>();
		_MView->AddView(Sub, SubCamera);
		SubCamera->SetEye(eye[2]);
		SubCamera->SetAt(at);

	}

	void TestStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");
	}

	void TestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
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
