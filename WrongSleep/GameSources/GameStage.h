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
	//	TestStage�N���X
	//--------------------------------------------------------------------------------------
	class TestStage :public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
		//�v���C���[�̍쐬
		void CreatePlayer();

		void DebugLine();
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�^�C�����O�{�b�N�X�̍쐬
		void CreateTilingFixedBox();
	public:
		//�\�z�Ɣj��
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;
	};
}
//end basecross

