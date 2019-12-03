#pragma once
#include "stdafx.h"

namespace basecross {
	
	//�O����`
	class EnemyManager;
	//-----------------------------------------
	//�Q�[���}�l�[�W���[�N���X����
	//-----------------------------------------
	class GameManager final:public ObjectInterface
	{
		// �f���[�^�[
		struct GMDeleter
		{
			void operator()(GameManager *p) { delete p; }
		};
		static unique_ptr<GameManager, GMDeleter> m_Ins;		///< Singleton�ŗ��p���鎩�����g�̃|�C���^

		explicit GameManager(const shared_ptr<StageBase>&StagePtr);

		~GameManager(){}

		shared_ptr<GameObject> _DebugObj;

		shared_ptr<StageBase> _TargetStage;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �V���O���g���\�z�ƃA�N�Z�T�i�\�z���͂��ׂẴp�����[�^��ݒ肷��j
		@return	Manager��unique_ptr
		*/
		//--------------------------------------------------------------------------------------
		static unique_ptr<GameManager, GMDeleter>& CreateManager(const shared_ptr<StageBase>&StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �V���O���g���A�N�Z�T
		@return	Manager��unique_ptr
		*/
		//--------------------------------------------------------------------------------------
		static unique_ptr<GameManager, GMDeleter>& GetManager();
		//--------------------------------------------------------------------------------------
		/*!
		@brief Manager���쐬����Ă邩�`�F�b�N
		@return	�쐬����Ă����true
		*/
		//--------------------------------------------------------------------------------------
		static bool MakeCheck();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����j��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		static void DeleteManager();

		void OnCreate()override;

		shared_ptr<EnemyManager> GetEnemyManager()const
		{
			return _EnemyManager;
		}

		void SetEnemyManager(shared_ptr<EnemyManager> &EnemyM)
		{
			_EnemyManager = EnemyM;
		}

		friend EnemyManager;
	private:
		//		
		shared_ptr<EnemyManager> _EnemyManager;
		//�R�s�[�֎~
		GameManager(const GameManager&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		//���[�u�֎~
		GameManager(const GameManager&&) = delete;
		GameManager& operator=(const GameManager&&) = delete;

	};

	
	class DebugObj :public GameObject
	{
	public:
		DebugObj(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr)
		{
		}

		void OnCreate()override;
		void OnUpdate()override;
	};

}