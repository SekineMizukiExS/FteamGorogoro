/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

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
	//StartStage�N���X
	//--------------------------------------------------------------------------------------
	class StartStage :public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		StartStage():Stage(){}
		virtual ~StartStage(){}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	TestStage�N���X
	//--------------------------------------------------------------------------------------
	class Futon;
	class TestStage :public Stage
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
		void CreateStageObject();

		void ToMyCamera();

		shared_ptr<MultiView>_MView;

		shared_ptr<Futon> _Ts;
	public:
		//�\�z�Ɣj��
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		shared_ptr<MultiView>GetMultiView()const
		{
			return _MView;
		}
	};
}
//end basecross

