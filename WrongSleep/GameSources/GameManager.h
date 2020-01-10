#pragma once
#include "stdafx.h"

namespace basecross {
	
	//�O����`
	class EnemyManager;

	//�X�e�[�W�^�C�v(�f�[�^���[�h���Ɏg�p�j
	enum class StageType
	{
		TitleStage,
		SelectStage,
		LoadStage,
		GameStage,
	};

	//-----------------------------------------
	//�Q�[���}�l�[�W���[�N���X����(�X�e�[�W���؂�ւ��x�Ƀ��Z�b�g)
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

		map<wstring,shared_ptr<BaseResource>> _ResMap;		///<-�X�e�[�W�Ǝ��Ŏg�p���郊�\�[�X 

		std::mutex _mutex;										///<-�}���`�X���b�h�p
		bool _LoadEnd = false;									///<<-���[�h�I��������True

	public:
		//static�֐�
		//--------------------------------------------------------------------------------------
		/*!
		@brief �V���O���g���\�z�ƃA�N�Z�T�i�\�z���͂��ׂẴp�����[�^��ݒ肷��j
		@param[in]�@StagePtr�@�^�[�Q�b�g�X�e�[�W(�f�t�H���g��nullptr)
		@return	Manager��unique_ptr
		*/
		//--------------------------------------------------------------------------------------
		static unique_ptr<GameManager, GMDeleter>& CreateManager(const shared_ptr<StageBase>&StagePtr = nullptr);
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
		//!static
		//--------------------------------------------------------------------------------------
		/*!
		@brief �i�s�x�̕ۑ�
		@param 
		@return
		@info 
			�ǂꂭ�炢�i�񂾂��O���f�[�^�ɕۑ����܂��B
			�X�e�[�W�𒆒f�����Ƃ��ۑ������s����B
			�`�F�b�N�|�C���g��ʉ߂�����ۑ������s����B
			��]�F�ʃX���b�h�Ŏ��s���A�I��������True
		*/
		//--------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����j��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void LoadStart(const StageType type);

		void OnCreate()override;

		void OnEvent(const shared_ptr<Event>&event)override;

		//void OnUpdate();

		//�Q�b�^�[
		shared_ptr<EnemyManager> GetEnemyManager()const
		{
			return _EnemyManager;
		}
		
		//���\�[�X�̓Ǎ����I�������True	
		bool GetLoadEnd()const
		{
			return _LoadEnd;
		}

		//�Z�b�^�[
		void SetEnemyManager(shared_ptr<EnemyManager> &EnemyM)
		{
			_EnemyManager = EnemyM;
		}

		void ChangeEventCamera();

		friend EnemyManager;
		
	private:
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���\�[�X�̓Ǎ�
		@param[in]	�Z���N�g�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		void LoadResource(const StageType type);

		//Tex
		void TextureLoad(const wstring& Key, const wstring& TextureFileName, const wstring& TexType = L"WIC")
		{
			auto Res = App::GetApp()->RegisterTexture(Key, TextureFileName, TexType);
			_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//wav
		void AudioLoad(const wstring& Key, const wstring& WavFileName)
		{
			auto Res = App::GetApp()->RegisterWav(Key, WavFileName);
			_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//Effect
		void EffectLoad(const wstring& Key, const wstring& EfkFileName, float magnification)
		{
			auto EfkInter = App::GetApp()->GetScene<Scene>()->GetEfkInterface();
			auto Res = App::GetApp()->RegisterEffect(Key, EfkFileName, EfkInter, magnification);
			_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}
		//		
		shared_ptr<EnemyManager> _EnemyManager;
	};

	//GameManagerState
	//�f�[�^���[�h��
	class DataLoadState :public ObjState<GameManager>
	{
		DECLARE_SINGLETON_INSTANCE(DataLoadState)
	public:
		void Enter(const shared_ptr<GameManager>&obj)override;
		void Execute(const shared_ptr<GameManager>&obj)override;
		void Exit(const shared_ptr<GameManager>&obj)override;
	};
	//�Q�[�����s��
	class ExecuteGameState :public ObjState<GameManager>
	{
		DECLARE_SINGLETON_INSTANCE(ExecuteGameState)
	public:
		void Enter(const shared_ptr<GameManager>&obj)override;
		void Execute(const shared_ptr<GameManager>&obj)override;
		void Exit(const shared_ptr<GameManager>&obj)override;
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