#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	///	GameEvent�C���^�[�t�F�C�X
	//--------------------------------------------------------------------------------------
	void GameEventInterface::SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
		const wstring& MsgStr, const GameEventType Type)
	{
		GameManager::GetManager()->GetGameEventDispatcher()->SendEvent(Sender, Receiver, MsgStr, Type);
	}

	void GameEventInterface::SendGameEvent(const shared_ptr<GameEventInterface>& Sender,
		const wstring& MsgStr, const GameEventType Type)
	{
		GameManager::GetManager()->GetGameEventDispatcher()->SendEvent(Sender, MsgStr, Type);
	}

	void GameEventInterface::SendGameEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
		const wstring& MsgStr, const GameEventType Type)
	{
		GameManager::GetManager()->GetGameEventDispatcher()->SendEvent(Sender, ReceiverKey, MsgStr, Type);
	}


	//--------------------------------------------------------------------------------------
	//	struct EventDispatcher::Impl;
	//	�p�r: Impl�\����
	//--------------------------------------------------------------------------------------
	struct GameEventDispatcher::Impl {
		//�C�x���g�̃L���[

		map<wstring, vector<weak_ptr<GameEventInterface>>> m_EventInterfaceGroupMap;

		weak_ptr<EventCameraMan> m_EventCameraMan;
		//
		//--------------------------------------------------------------------------------------
		//	void Discharge(
		//	const Event& event	//�C�x���g
		//	);
		//�p�r: �C�x���g�̑��M
		//�߂�l: �Ȃ�
		//--------------------------------------------------------------------------------------
		void Discharge(const shared_ptr<GameEvent>& event);
		Impl() {}
		~Impl() {}
	};

	void GameEventDispatcher::Impl::Discharge(const shared_ptr<GameEvent>& event) {
		auto shptr = event->m_Receiver.lock();
		if (shptr) {
			//�󂯎肪�L��
			shptr->OnGameEvent(event);
		}
	}



	//--------------------------------------------------------------------------------------
	///	�C�x���g�z���N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	GameEventDispatcher::GameEventDispatcher() :
		pImpl(new Impl())
	{}
	GameEventDispatcher::~GameEventDispatcher() {}

	void GameEventDispatcher::AddEventReceiverGroup(const wstring& GroupKey, const shared_ptr<GameEventInterface>& Receiver) {
		auto it = pImpl->m_EventInterfaceGroupMap.find(GroupKey);
		if (it != pImpl->m_EventInterfaceGroupMap.end()) {
			//�L�[��������
			it->second.push_back(Receiver);
		}
		else {
			//�O���[�v���Ȃ�
			vector<weak_ptr<GameEventInterface>> vec;
			pImpl->m_EventInterfaceGroupMap[GroupKey] = vec;
			pImpl->m_EventInterfaceGroupMap[GroupKey].push_back(Receiver);
		}
	}

	void GameEventDispatcher::AddEventCameraMan(const shared_ptr<EventCameraMan>& Receiver)
	{
		auto Obj = pImpl->m_EventCameraMan.lock();
		if (!Obj)
		{
			pImpl->m_EventCameraMan = Receiver;
		}
		return;
	}

	//�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
	void GameEventDispatcher::SendEvent(const shared_ptr<GameEventInterface>& Sender, const shared_ptr<GameEventInterface>& Receiver,
		const wstring& MsgStr, const GameEventType Type) {
		//�C�x���g�̍쐬 
		auto Ptr = make_shared<GameEvent>(Sender, Receiver, MsgStr, Type);
		//���M
		TypeEvent(Ptr);
	}

	//�C�x���g��SEND�i�L���[�ɓ��ꂸ�ɂ��̂܂ܑ���j
	void GameEventDispatcher::SendEvent(const shared_ptr<GameEventInterface>& Sender,
		const wstring& MsgStr, const GameEventType Type) {
		//�C�x���g�̍쐬 
		auto Ptr = make_shared<GameEvent>(Sender, nullptr, MsgStr, Type);
		//���M
		TypeEvent(Ptr);
	}

	void GameEventDispatcher::SendEvent(const shared_ptr<GameEventInterface>& Sender, const wstring& ReceiverKey,
		const wstring& MsgStr, const GameEventType Type) {
		//ReceiverKey�ɂ�鑊��̓���
		//�d���L�[�̌���
		auto it = pImpl->m_EventInterfaceGroupMap.find(ReceiverKey);
		if (it != pImpl->m_EventInterfaceGroupMap.end()) {
			//�L�[��������
			for (auto v : it->second) {
				auto shptr = v.lock();
				if (shptr) {
					//�C�x���g�̍쐬 
					auto Ptr = make_shared<GameEvent>(Sender, shptr, MsgStr, Type);
					//�C�x���g�̑��o
					TypeEvent(Ptr);
				}
			}
		}
		//�L�[��������Ȃ��Ă��������Ȃ�
	}

	void GameEventDispatcher::TypeEvent(const shared_ptr<GameEvent>& gameevent)
	{
		GameEventType type = gameevent->m_Type;
		shared_ptr<EventCameraMan> ECM;
		shared_ptr<MovingObject> ER;
		shared_ptr<LoadBlock> LB;
		shared_ptr<SaveDataObject> SDObj;
		wstring DataPath;
		SaveData DataFile;

		switch (type)
		{
			//�ʏ�C�x���g
		case basecross::GameEventType::Default:
			pImpl->Discharge(gameevent);
			break;
			//�M�~�b�N�C�x���g
		case basecross::GameEventType::Gimmick:
			pImpl->Discharge(gameevent);
			break;
			//�J�����ړ��M�~�b�N�C�x���g
		case basecross::GameEventType::GimmickAction:
			/*
			*�J�������ړ�������
			*�ړ�����������C�x���g��΂�
			*/
			ECM = pImpl->m_EventCameraMan.lock();
			ER = dynamic_pointer_cast<MovingObject>(gameevent->m_Receiver.lock());
			ECM->SetTargetObject(ER);
			ECM->SetGameEvent(gameevent);
			ECM->GetStateMachine()->ChangeState(MoveToEventPoint::Instance());
			break;
			//�X�e�[�W�ړ��C�x���g
		case basecross::GameEventType::MoveStage:
			LB = dynamic_pointer_cast<LoadBlock>(gameevent->m_Sender.lock());
			if (gameevent->m_MsgStr == L"Result")
			{
				GameManager::GetManager()->PostEvent(0.0f, nullptr, App::GetApp()->GetScene<Scene>(), L"ToResultStage");
				return;
			}
			GameManager::GetManager()->SetXMLFilePath(gameevent->m_MsgStr);
			GameManager::GetManager()->SetLoadPosKey(LB->GetTargetPosStr());
			GameManager::GetManager()->PostEvent(0.0f, nullptr, App::GetApp()->GetScene<Scene>(), L"ToMainGameStage");
			break;
			//�J�b�g�V�[���E�C�x���g�V�[���C�x���g
		case basecross::GameEventType::CutScene:
			//�C�x���g�����n�_��Key���擾����
			//
			break;
			//�Z�[�u�f�[�^�I��
		case basecross::GameEventType::SaveDataIO:
			SDObj = dynamic_pointer_cast<SaveDataObject>(gameevent->m_Sender.lock());
			DataPath = SDObj->GetSaveDataPath();
			DataFile = GameManager::GetManager()->GetDataIO()->ReadDataFile(DataPath);
			GameManager::GetManager()->SetSaveData(DataFile,DataPath);
			GameManager::GetManager()->PostEvent(0.0f, nullptr, App::GetApp()->GetScene<Scene>(), L"ToMainGameStage");
			break;
		default:
			break;
		}
	}

	//-----------------------------------------------------------------
	///GameManager�N���X
	//-----------------------------------------------------------------

	//static�ϐ�����
	unique_ptr<GameManager, GameManager::GMDeleter> GameManager::m_Ins;
	//�\�z�Ɣj��
	GameManager::GameManager()
		:_TargetStage(nullptr),_XMLFileName(L"TStageMap"),_LoadPosKey(L"PlayerStart"),MaxMoveCount(10000),m_CurrntKeyNums(0)
	{
		_EnemyManager = ObjectFactory::Create<EnemyManager>();
		m_GameEventDispatcher = make_shared<GameEventDispatcher>();
		m_DataIO = make_shared<DataBinaryIO>();
	}


	//�V���O���g���\�z
	unique_ptr<GameManager, GameManager::GMDeleter>& GameManager::CreateManager() {
		try {
			if (m_Ins.get() == 0) {
				//�������g�̍\�z
				m_Ins.reset(new GameManager());
				m_Ins->OnPreCreate();
				m_Ins->OnCreate();
			}
			return m_Ins;
		}
		catch (...) {
			throw;
		}
	}

	//�V���O���g���A�N�Z�T
	unique_ptr < GameManager, GameManager::GMDeleter > & GameManager::GetManager() {
		try {
			if (m_Ins.get() == 0) {
				throw BaseException(
					L"�}�l�[�W���[���܂��쐬����Ă܂���",
					L"if (m_Ins.get() == 0)",
					L"GameManager::GetManager()"
				);
			}
			return m_Ins;
		}
		catch (...) {
			throw;
		}

	}

	bool GameManager::MakeCheck() {
		if (m_Ins.get() == 0) {
			return false;
		}
		return true;
	}

	//�����j��
	void GameManager::DeleteManager() {
		if (m_Ins.get()) {
			m_Ins.reset();
		}
	}

	void GameManager::SaveGameData()
	{
		m_DataIO->SetSaveParam(_XMLFileName, _LoadPosKey, _CumulativeTime);
		m_DataIO->WriteDataFile(_CurrntSaveDataPath);
	}

	void GameManager::LoadStart()
	{
		std::thread LoadThread(&GameManager::LoadResource, this);
		LoadThread.detach();
	}

	//
	void GameManager::LoadResource()
	{
		_mutex.lock();
		_LoadEnd = false;
		_ResMap.clear();
		_mutex.unlock();

		//���f�B�A�p�X
		wstring mediaPath;
		App::GetApp()->GetDataDirectory(mediaPath);
		wstring TexturePath = mediaPath + L"Textures/";
		wstring ModelPath = mediaPath + L"Models/";
		wstring EffectPath = mediaPath + L"Effect/";
		wstring BGMPath = mediaPath + L"Sounds/BGM/";
		wstring SEPath = mediaPath + L"Sounds/SE/";

		//���\�[�X�̓Ǎ�
		App::GetApp()->RegisterTexture(L"Test_TX", TexturePath + L"KB.png");
		App::GetApp()->RegisterTexture(L"LeafMat_TX", TexturePath + L"leafmat_tx.png");
		App::GetApp()->RegisterTexture(L"LeafMatB_TX", TexturePath + L"leafmatBlack_tx.png");
		App::GetApp()->RegisterTexture(L"Player_TX", TexturePath + L"Tx_Player.png");
		App::GetApp()->RegisterTexture(L"Player002_TX", TexturePath + L"Tx_Player002.png");
		App::GetApp()->RegisterTexture(L"RedApple_TX", TexturePath + L"Tx_RedApple.png");
		App::GetApp()->RegisterTexture(L"clearG_TX", TexturePath + L"clearGreen.png");
		App::GetApp()->RegisterTexture(L"clearmat_TX", TexturePath + L"clearmat.png");
		App::GetApp()->RegisterTexture(L"skybox_TX", TexturePath + L"skybox_tx.png");
		App::GetApp()->RegisterTexture(L"Title_TX", TexturePath + L"Title-Logo.png");
		App::GetApp()->RegisterTexture(L"Clear_TX", TexturePath + L"Clear.png");

		App::GetApp()->RegisterTexture(L"Start_TX", TexturePath + L"Start01.png");

		App::GetApp()->RegisterTexture(L"Bridge_TX", TexturePath + L"Tx_Bridge.png");
		App::GetApp()->RegisterTexture(L"Fence_TX", TexturePath + L"Tx_Fence.png");
		App::GetApp()->RegisterTexture(L"Flower_TX", TexturePath + L"Tx_Flower.png");
		App::GetApp()->RegisterTexture(L"WarpPad_TX", TexturePath + L"Tx_WarpPad.png");
		App::GetApp()->RegisterTexture(L"Tree_TX", TexturePath + L"Tx_Tree.png");
		App::GetApp()->RegisterTexture(L"Pedestal_TX", TexturePath + L"Tx_Pedestal.png");
		App::GetApp()->RegisterTexture(L"NUMBER_TX", TexturePath + L"number.png");
		//���f���e�N�X�`��
		App::GetApp()->RegisterTexture(L"Button_TX", ModelPath + L"Tx_Button.png");
		App::GetApp()->RegisterTexture(L"Key_TX", TexturePath + L"Tx_Key.png");

		auto modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"MatTest.bmf", true);
		App::GetApp()->RegisterResource(L"MatTest_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"PlayerModel.bmf");
		App::GetApp()->RegisterResource(L"Player_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"Player2.bmf");
		App::GetApp()->RegisterResource(L"Player2_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"Mat.bmf", true);
		App::GetApp()->RegisterResource(L"Mat_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"Apple2.bmf", true);
		App::GetApp()->RegisterResource(L"Apple_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"skyboxObj.bmf", true);
		App::GetApp()->RegisterResource(L"SkyBox_MD", modelMesh);

		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"Key.bmf", true);
		App::GetApp()->RegisterResource(L"Key_MD", modelMesh);

		modelMesh = MeshResource::CreateBoneModelMesh(ModelPath, L"Button.bmf");
		App::GetApp()->RegisterResource(L"Switch_MD", modelMesh);

		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"SAModel_bridge.bmf");
		App::GetApp()->RegisterResource(L"Bridge_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"SAModel_Fence.bmf");
		App::GetApp()->RegisterResource(L"Fence_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"SAModel_Flower.bmf");
		App::GetApp()->RegisterResource(L"Flower_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"SAModel_WarpPad.bmf");
		App::GetApp()->RegisterResource(L"WarpPad_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"SAModel_Tree.bmf");
		App::GetApp()->RegisterResource(L"Tree_MD", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(ModelPath, L"Pedestal.bmf");
		App::GetApp()->RegisterResource(L"Pedestal_MD", modelMesh);

		App::GetApp()->RegisterResource(L"TestCube", MeshResource::CreateCube(1.0f, true));

		//���f��
		App::GetApp()->RegisterWav(L"MainBGM_SD", BGMPath + L"MainMusicT.wav");
		App::GetApp()->RegisterWav(L"PuttingSE_SD", SEPath + L"putting_a_box.wav");
		App::GetApp()->RegisterWav(L"SelectSE_SD", SEPath + L"Select.wav");

		_mutex.lock();
		_LoadEnd = true;
		_mutex.unlock();
	}
	//

	void GameManager::SetSettingPosData(const wstring& FilePath)
	{
		_SettingPosData.clear();
		auto XMLRead = new XmlDocReader(FilePath);
		auto SDataNodes = XMLRead->GetSelectNodes(L"root/settingData/posDatas/SetPosData");

		long NodeCount = XmlDocReader::GetLength(SDataNodes);
		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		for (long i = 0; i < NodeCount; i++)
		{
			auto Node = XmlDocReader::GetItem(SDataNodes, i);
			auto PosStr = XmlDocReader::GetAttribute(Node, L"Position");
			auto PosKey = XmlDocReader::GetAttribute(Node, L"PosKey");

			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			//Position
			Tokens.clear();
			Util::WStrToTokenVector(Tokens, PosStr, L',');
			//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
			Vec3 Pos = Vec3(
				(float)_wtof(Tokens[0].c_str()),
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			_SettingPosData[PosKey] = Pos;
		}

		//�X�e�[�W�N���A������ǂݍ���
		auto StageNode = XMLRead->GetSelectSingleNode(L"root/Stage");
		//���̌�
		auto KeyNumStr = XmlDocReader::GetAttribute(StageNode, L"KeyNum");

		MaxKeyNums = (int)_wtoi(KeyNumStr.c_str());

		//Bonus�A�C�e���̌�

		//�ړ��񐔐���
		auto MoveMaxLimitStr = XmlDocReader::GetAttribute(StageNode, L"MoveLimit");
		MaxMoveCount = (int)_wtoi(MoveMaxLimitStr.c_str());
		m_CurrntKeyNums = 0;
	}

	void GameManager::OnCreate()
	{
		
		//_TargetStage->AddGameObject<DebugObj>();
	}

	void GameManager::OnEvent(const shared_ptr<Event>&event)
	{
		if (event->m_MsgStr == L"Save")
		{
			SaveGameData();
		}
	}

	void GameManager::ChangeEventCamera()
	{
		
	}

	void GameManager::OnUpdate()
	{
		auto Delta = App::GetApp()->GetElapsedTime();
		_CumulativeTime += Delta;
	}

	//-----------------------------------------------------------

	void DebugObj::OnCreate()
	{
		//Debug
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 50.0f, 640.0f, 480.0f));

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}

	void DebugObj::OnUpdate()
	{
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		fpsStr += Util::FloatToWStr(ElapsedTime);
		fpsStr += L"\n";

		wstring updatePerStr(L"UpdatePerformance:\t");
		updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		updatePerStr += L"\tmillisecond\n";

		wstring drawPerStr(L"DrawPerformance:\t");
		drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		drawPerStr += L"\tmillisecond\n";

		wstring collPerStr(L"CollisionPerform:\t");
		collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		collPerStr += L"\tmillisecond\n";

		wstring collMiscStr(L"ColMiscPerform:\t");
		collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		collMiscStr += L"\tmillisecond\n";

		wstring collTernCountStr(L"CollisionCountOfTern:\t");
		collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		collTernCountStr += L"\n";

		wstring ObjCount(L"ObjectCount:\t");
		ObjCount += Util::UintToWStr((UINT)GetStage()->GetGameObjectVec().size());
		ObjCount += L"\n";

		wstring str = fpsStr + updatePerStr + drawPerStr + collPerStr + collMiscStr
			+ collTernCountStr + ObjCount;

		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);


	}
}