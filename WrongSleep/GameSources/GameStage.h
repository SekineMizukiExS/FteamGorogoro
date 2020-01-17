/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera;

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�x�[�X�N���X�i�G�t�F�N�g�̍X�V�E�`��j
	//--------------------------------------------------------------------------------------
	enum  SelectCamera
	{
		pMyCamera,
		pEventCamera
	};

	class StageBase : public Stage {
		shared_ptr<EfkPlay> m_EfkPlay[50];
		int m_EfkCount = 0;

	public:
		//�\�z�Ɣj��
		StageBase() :Stage(), _MView(nullptr), _MyCameraIndex(NULL), _SubCametaIndex(NULL){}
		virtual ~StageBase() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//�`��
		void OnDraw()override;

		void OnDestroy()override;

		SelectCamera GetCameraSelects()const {
			return _Camera;
		}

		void Effectplay(wstring Key, Vec3 hitpoint);
	protected:
		//�r���[�̍쐬
		virtual void CreateViewLight() = 0;

		shared_ptr<MultiView>_MView;
		shared_ptr<SingleView>_EventView;
		//
		size_t _MyCameraIndex;
		size_t _SubCametaIndex;
		SelectCamera _Camera;

	};
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�v���C���[�̍쐬
		void CreatePlayer();

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
	};

	//--------------------------------------------------------------------------------------
	//TitleStage�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage :public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		TitleStage():Stage(){}
		virtual ~TitleStage(){}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//LoadStage�N���X�i�ǂݍ��ރX�e�[�W�j
	//--------------------------------------------------------------------------------------
	class LoadStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateLoadSprite();
		////���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
		//static void LoadResourceFunc();
		////���\�[�X��ǂݍ��񂾂��Ƃ�m�点��t���O�i�X�^�e�B�b�N�ϐ��j
		//static bool m_Loaded;
		////�~���[�e�b�N�X
		//static std::mutex mtx;
	public:
		//�\�z�Ɣj��
		LoadStage() :Stage() {}
		virtual ~LoadStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//SelectStage�N���X�i����j
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//MainGameStage�N���X
	//--------------------------------------------------------------------------------------
	class MainGameStage :public StageBase
	{
		void CreateViewLight()override;

	public:
		//�\�z�Ɣj��
		MainGameStage();
		~MainGameStage();
		//������
		void OnCreate()override;
		//�X�V
		void OnUpdate()override;
		//�`��
		void OnDraw()override;
	};
	//--------------------------------------------------------------------------------------
	//Movie�N���X
	//--------------------------------------------------------------------------------------
	class MyMovieStage :public MovieStage
	{
	public:
		//�\�z�Ɣj��
		MyMovieStage() :MovieStage() {}
		virtual ~MyMovieStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
	//--------------------------------------------------------------------------------------
	//	TestStage�N���X
	//--------------------------------------------------------------------------------------
	class Futon;
	class TestStage :public StageBase
	{
		//�I�[�v�j���O�̃{�X�ւ̃t�H�[�J�X�p�r���[
		shared_ptr<SingleView> m_MyCameraView;


		//�r���[�̍쐬
		void CreateViewLight();
		//�v���C���[�̍쐬
		void CreatePlayer();

		void DebugLine();
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�^�C�����O�{�b�N�X�̍쐬
		void CreateTilingFixedBox();
		//�J�X�^�����b�V���{�b�N�X�̍쐬
		void CreateCMeshBox();
		void CreateCommonBox();
		void CreateStageObject();

		void SetCellMapCost();
	public:
		//�\�z�Ɣj��
		TestStage() :StageBase() {}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		void ToMyCamera();

		void ToEventCamera();

		shared_ptr<MyCamera>GetMyCamera()const
		{
			return dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		}
	};
}
//end basecross

