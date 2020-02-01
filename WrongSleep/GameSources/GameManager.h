#pragma once
#include "stdafx.h"

namespace basecross {
	
	//�O����`
	class EnemyManager;
	struct GameEvent;
	class EventCameraMan;
	class DataBinaryIO;

	//------------------------------------------------------
	//�Z�[�u�f�[�^�`��
	//------------------------------------------------------
	struct SaveData
	{
		//�O��I�����̃}�b�v��
		wstring LastMapName;
		//�O��}�b�v�̓Ǎ����̃v���C���[�n�_��
		wstring LastLoadBlock;
		//�݌v�v���C����
		float CumulativeTime;

		SaveData(){}
		SaveData(const wstring& MapName, const wstring& LoadBlock, const float& Time)
			:LastMapName(MapName), LastLoadBlock(LoadBlock), CumulativeTime(Time)
		{}
	};

	//�Q�[���C�x���g�^�C�v
	/*
	*0�W��
	*1�M�~�b�N�쓮
	*2�M�~�b�N�쓮�i�J����������)
	*3�X�e�[�W�J�ځi�X�e�[�W�f�[�^�Ǎ��j
	*4�J�b�g�V�[���i����j
	*/
	enum class GameEventType
	{
		Default,
		Gimmick,
		GimmickAction,
		MoveStage,
		CutScene,
		SaveDataIO
	};

	class GameEventInterface
	{
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �v���e�N�g�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		GameEventInterface() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �v���e�N�g�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameEventInterface() {}
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
		@param[in]	Sender	�C�x���g���M�ҁinullptr�j
		@param[in]	ReceiverKey	�󂯎葤�I�u�W�F�N�g�𔻕ʂ���L�[
		@param[in]	MsgStr	���b�Z�[�W
		@param[in,out] Type �C�x���g�^�C�v
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
		@param[in]	Sender	�C�x���g���M�ҁinullptr�j
		@param[in]	ReceiverKey	�󂯎葤�I�u�W�F�N�g�𔻕ʂ���L�[
		@param[in]	MsgStr	���b�Z�[�W
		@param[in,out] Type �C�x���g�^�C�v
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SendGameEvent(const shared_ptr<GameEventInterface>& Sender,
			const wstring& MsgStr, const GameEventType Type = GameEventType::MoveStage);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
		@param[in]	Sender	�C�x���g���M�ҁinullptr�j
		@param[in]	Receiver	�C�x���g��M�ҁinullptr�s�j
		@param[in]	MsgStr	���b�Z�[�W
		@param[in,out] Type �C�x���g�^�C�v
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g���󂯎��
		@param[in]	event	�C�x���g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnGameEvent(const shared_ptr<GameEvent>& event) {}
	private:
		//�R�s�[�֎~
		GameEventInterface(const GameEventInterface&) = delete;
		GameEventInterface& operator=(const GameEventInterface&) = delete;
		//���[�u�֎~
		GameEventInterface(const GameEventInterface&&) = delete;
		GameEventInterface& operator=(const GameEventInterface&&) = delete;

	};

	//-----------------------------------------
	///�Q�[���C�x���g�\����
	//-----------------------------------------
	struct GameEvent
	{
		///	���̃��b�Z�[�W�𑗂����I�u�W�F�N�g
		weak_ptr<GameEventInterface> m_Sender;
		///	�󂯎��I�u�W�F�N�g�inullptr�̏ꍇ�̓Q�[���}�l�[�W���[�������̓L�[���[�h�Ŏ��ʂ���I�u�W�F�N�g�j
		weak_ptr<GameEventInterface> m_Receiver;
		///	���b�Z�[�W������
		wstring m_MsgStr;
		///�Q�[���C�x���g�^�C�v
		GameEventType m_Type;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	DispatchTime	�z���܂ł̎���
		@param[in]	Sender	���葤�I�u�W�F�N�g�inullptr�j
		@param[in]	Receiver	�󂯎葤�I�u�W�F�N�g
		@param[in]	MsgStr	���b�Z�[�W������
		@param[in]	Type �C�x���g�^�C�v
		*/
		//--------------------------------------------------------------------------------------
		GameEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default) :
			m_Sender(Sender),
			m_Receiver(Receiver),
			m_MsgStr(MsgStr),
			m_Type(Type)
		{}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		~GameEvent() {}
	};

	//--------------------------------------------------------------------------------------
	///	�C�x���g�z���N���X
	//--------------------------------------------------------------------------------------
	class GameEventDispatcher {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	SceneBasePtr	�V�[���x�[�X�̃|�C���^
		*/
		//--------------------------------------------------------------------------------------
		explicit GameEventDispatcher();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameEventDispatcher();


		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g���󂯎��O���[�v�ɒǉ��i�O���[�v���Ȃ���΂��̖��O�ō쐬�j
		@param[in]	GroupKey	�O���[�v��
		@param[in]	Receiver	�󂯎葤�I�u�W�F�N�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddEventReceiverGroup(const wstring& GroupKey, const shared_ptr<GameEventInterface>& Receiver);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g�J�����}���̐ݒ�
		@param[in]	Receiver	�J�����}���I�u�W�F�N�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddEventCameraMan(const shared_ptr<EventCameraMan>& Receiver);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
		@param[in]	Sender	���葤�I�u�W�F�N�g�inullptr�j
		@param[in]	Receiver	�󂯎葤�I�u�W�F�N�g
		@param[in]	MsgStr	���b�Z�[�W������
		@param[in]	Info	�ǉ����������[�U�[�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SendEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
		@param[in]	Sender	���葤�I�u�W�F�N�g�inullptr�j
		@param[in]	Receiver	�󂯎葤�I�u�W�F�N�g
		@param[in]	MsgStr	���b�Z�[�W������
		@param[in]	Info	�ǉ����������[�U�[�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SendEvent(const shared_ptr<GameEventInterface>& Sender,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
		@param[in]	Sender	�C�x���g���M�ҁinullptr�j
		@param[in]	Receiver	�C�x���g��M�ҁinullptr�s�j
		@param[in]	MsgStr	���b�Z�[�W
		@param[in,out]	Info	�ǉ����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SendEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
			const wstring& MsgStr, const GameEventType Type = GameEventType::Default);
	private:
		//--------------------------------------------------------------------------------------
		/*!
		@brief Type���Ƃ̏�������
		@param[in]	
		@return	bool
		*/
		//--------------------------------------------------------------------------------------
		void TypeEvent(const shared_ptr<GameEvent>& gameevent);
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
		//�R�s�[�֎~
		GameEventDispatcher(const GameEventDispatcher&) = delete;
		GameEventDispatcher& operator=(const GameEventDispatcher&) = delete;
		//���[�u�֎~
		GameEventDispatcher(const GameEventDispatcher&&) = delete;
		GameEventDispatcher& operator=(const GameEventDispatcher&&) = delete;
	};


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
	class GameManager :public ObjectInterface
	{
		// �f���[�^�[
		struct GMDeleter
		{
			void operator()(GameManager *p) { delete p; }
		};
		static unique_ptr<GameManager, GMDeleter> m_Ins;		///< Singleton�ŗ��p���鎩�����g�̃|�C���^

		explicit GameManager();

		~GameManager(){}

		shared_ptr<GameObject> _DebugObj;

		shared_ptr<Stage> _TargetStage;

		map<wstring,shared_ptr<BaseResource>> _ResMap;		///<-�X�e�[�W�Ǝ��Ŏg�p���郊�\�[�X 
		shared_ptr<GameEventDispatcher> m_GameEventDispatcher;	///< �C�x���g���M�I�u�W�F�N�g

		shared_ptr<DataBinaryIO> m_DataIO;

		map<wstring, Vec3> _SettingPosData; ///<-�����z�u�f�[�^�Q

		int MaxKeyNums;						///<-�N���A�ɕK�v�Ȍ���

		int m_CurrntKeyNums;

		int MaxMoveCount;					///<-�X�e�[�W��ňړ��ł����

		wstring _CurrntSaveDataPath;

		wstring _XMLFileName;

		wstring _LoadPosKey;

		float _CumulativeTime; ///<-�݌v�v���C����

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
		static unique_ptr<GameManager, GMDeleter>& CreateManager();
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
		void SaveGameData();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�W�̔z�u
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------
		/*!
		@brief �����j��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void LoadStart();

		void OnCreate()override;

		void OnUpdate();

		void OnEvent(const shared_ptr<Event>&event)override;

		//void OnGameEvent(const shared_ptr<GameEvent>&gameevent);

		//void OnUpdate();

		//�Q�b�^�[
		shared_ptr<EnemyManager> GetEnemyManager()const
		{
			return _EnemyManager;
		}
		
		const wstring GetXMLFilePath()const { return _XMLFileName; }

		const wstring GetLoadPosKey()const { return _LoadPosKey; }

		const float &GetCumulativeTime()const { return _CumulativeTime; }

		const int &GetMaxMoveCount()const { return MaxMoveCount; }

		shared_ptr<GameEventDispatcher> GetGameEventDispatcher()const { return m_GameEventDispatcher; }

		shared_ptr<DataBinaryIO> GetDataIO()const { return m_DataIO; }

		const shared_ptr<Stage> GetTargetStage()const { return _TargetStage; }

		const Vec3 GetSettingPosData(const wstring& PosKey) { return _SettingPosData[PosKey]; }

		//����
		const bool CheckKeyVol() { return MaxKeyNums <= m_CurrntKeyNums; }

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

		void SetTargetStage(const shared_ptr<Stage> &stage)
		{
			_TargetStage = stage;
		}

		void SetXMLFilePath(const wstring &FilePath)
		{
			_XMLFileName = FilePath;
		}

		void SetLoadPosKey(const wstring &PosKey)
		{
			_LoadPosKey = PosKey;
		}

		void AddKeyNums(const int &Vol)
		{
			m_CurrntKeyNums += Vol;
		}

		void SetSaveData(const SaveData& SaveDataPtr,const wstring DataPath)
		{
			_CurrntSaveDataPath = DataPath;
			_XMLFileName = SaveDataPtr.LastMapName;
			_LoadPosKey = SaveDataPtr.LastLoadBlock;
			_CumulativeTime = SaveDataPtr.CumulativeTime;
		}

		void SetSettingPosData(const wstring& FilePath);

		void MovedPlayer() 
		{
			MaxMoveCount--;
			if (MaxMoveCount <= 0)
			{
				PostEvent(0.0f, nullptr, App::GetApp()->GetScene<Scene>(), L"ToMainGameStage");
			}
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
		void LoadResource();

		//Tex
		void TextureLoad(const wstring& Key, const wstring& TextureFileName, const wstring& TexType = L"WIC")
		{
			auto Res = App::GetApp()->RegisterTexture(Key, TextureFileName, TexType);
			//_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//wav
		void AudioLoad(const wstring& Key, const wstring& WavFileName)
		{
			auto Res = App::GetApp()->RegisterWav(Key, WavFileName);
			//_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
		}

		//Effect
		void EffectLoad(const wstring& Key, const wstring& EfkFileName, float magnification)
		{
			auto EfkInter = App::GetApp()->GetScene<Scene>()->GetEfkInterface();
			auto Res = App::GetApp()->RegisterEffect(Key, EfkFileName, EfkInter, magnification);
			//_ResMap[Key] = static_pointer_cast<BaseResource>(Res);
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