/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�x�[�X�N���X
	//--------------------------------------------------------------------------------------
	void StageBase::OnCreate()
	{

	}

	void StageBase::OnUpdate()
	{
		App::GetApp()->GetScene<Scene>()->GetEfkInterface()->OnUpdate();
	}

	void StageBase::OnDraw()
	{
		auto& camera = GetView()->GetTargetCamera();
		App::GetApp()->GetScene<Scene>()->GetEfkInterface()->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		App::GetApp()->GetScene<Scene>()->GetEfkInterface()->OnDraw();
	}

	void StageBase::OnDestroy()
	{

	}

	void StageBase::Effectplay(wstring Key, Vec3 hitpoint) {
		//�G�t�F�N�g�̃v���C********************************
		//auto TransformPtr = &tr;
		//auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();

		m_EfkPlay[m_EfkCount] = ObjectFactory::Create<EfkPlay>(Key, hitpoint);
		if (m_EfkCount == 19) {
			m_EfkCount = 0;
		}
		else {
			m_EfkCount++;
		}
	}

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, 5.0f);
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
	//	StartStage�N���X����
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight()
	{
		const Vec3 eye(50.0f, 0.0f, 0.0f);
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
		PtrMultiLight->SetDefaultLighting2();
	}

	void TitleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			AddGameObject<TitleUI>(L"Title_TX",true,Vec2(1,1),Vec3(0,0,0),Vec2(1280,800));
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate()
	{
		auto Dev = App::GetApp()->GetInputDevice();
		auto KeyB = Dev.GetKeyState();
		auto cont = Dev.GetControlerVec()[0];
		if (KeyB.m_bLastKeyTbl['G']||cont.wPressedButtons == XINPUT_GAMEPAD_START)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToLoadStage");
		}
	}

	//!endStartStage

	//--------------------------------------------------------------------------------------
	//LoadStage�N���X�i�ǂݍ��ރX�e�[�W�j
	//--------------------------------------------------------------------------------------
	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 10.0f, -20.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		auto ptrPlayer = GetSharedGameObject<PlayerMarker>(L"PlayerMarker");
		PtrCamera->SetTargetObject(ptrPlayer);
		PtrCamera->SetMinArm(1.0f);
		PtrCamera->SetMaxArm(50.0f);

		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}

	//�X�v���C�g�̍쐬
	void LoadStage::CreateLoadSprite() 
	{
		auto Obj1 = AddGameObject<SaveDataObject>(L"root/SaveData1", L"DEFAULT_CUBE", L"clearmat_TX", Vec3(-3, 0,0), Vec3(2, 2, 2), Vec3(0, 0, 0));
		auto Obj2 = AddGameObject<SaveDataObject>(L"root/SaveData2", L"DEFAULT_CUBE", L"clearmat_TX", Vec3(0, 0, 0), Vec3(2, 2, 2), Vec3(0, 0, 0));
		auto Obj3 = AddGameObject<SaveDataObject>(L"root/SaveData3", L"DEFAULT_CUBE", L"clearmat_TX", Vec3(3, 0, 0), Vec3(2, 2, 2), Vec3(0, 0, 0));
		AddGameObject<NumberSprite>(Obj1, L"NUMBER_TX", true, 1);
		AddGameObject<NumberSprite>(Obj2, L"NUMBER_TX", true, 2);
		AddGameObject<NumberSprite>(Obj3, L"NUMBER_TX", true, 3);
		
		AddGameObject<FixedBox>(Vec3(10, 0.5f, 10), Vec3(0), Vec3(0, -0.5f, 0));

		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");

		auto ptrPlayerMarker = AddGameObject<PlayerMarker>();
		ptrPlayerMarker->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerMarker", ptrPlayerMarker);

		auto ptrPlayerModel = AddGameObject<PlayerModel>();
		ptrPlayerModel->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerModel", ptrPlayerModel);

		ptrPlayer->GetComponent<Transform>()->SetPosition(Vec3(3, 0.5f, 4));
	}

	//������
	void LoadStage::OnCreate() 
	{
		StageBase::OnCreate();
		//�X�v���C�g�̍쐬
		CreateLoadSprite();
		CreateViewLight();
	}

	//�X�V
	void LoadStage::OnUpdate() {
		StageBase::OnUpdate();
		//if () {
		//	//���\�[�X�̃��[�h���I��������^�C�g���X�e�[�W�Ɉڍs
		//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		//}
	}

	//--------------------------------------------------------------------------------------
	//MainGameStage�N���X
	//--------------------------------------------------------------------------------------
	MainGameStage::MainGameStage()
		:StageBase()
	{
		CreateSharedObjectGroup(L"ResetObj");
	}

	MainGameStage::~MainGameStage(){}

	void MainGameStage::CreateViewLight() {
		const Vec3 eye[7] = { Vec3(0.0f, 5.0f, -5.0f),//�W���ʒu
							  Vec3(0.0f, 0.0f, -30.0f),
							  Vec3(0.0f, 20.0f, 00.1f),
							  Vec3(0.0f, 110.0f, -75.0f),
							  Vec3(0.0f,20.0f,50.0f),
							  Vec3(10.0f, 0.0f, -10.0f),
								Vec3(0.0f,15.0f,-10.0f) };
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
		Sub.TopLeftY = 0;
		Sub.Width = 280;
		Sub.Height = 100;
		Sub.MaxDepth = 1.0f;
		Sub.MinDepth = 0.0f;

		_MView = CreateView <MultiView>();


		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		//�J�����C���f�b�N�X
		_MyCameraIndex = _MView->AddView(Main, PtrCamera);
		PtrCamera->SetEye(eye[4]);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
		//�v���C���[�̏���n��
		auto ptrPlayer = GetSharedGameObject<PlayerMarker>(L"PlayerMarker");
		PtrCamera->SetTargetObject(ptrPlayer);
		PtrCamera->SetMinArm(1.0f);
		PtrCamera->SetMaxArm(50.0f);

		//�T�u�J����
		auto SubCamera = ObjectFactory::Create<Camera>();
		_SubCametaIndex = _MView->AddView(Sub, SubCamera);
		SubCamera->SetEye(eye[3]);
		SubCamera->SetAt(at);

		//�C�x���g�J������View�쐬
		_EventView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto EventCameraPtr = ObjectFactory::Create<EventCamera>();
		_EventView->SetCamera(EventCameraPtr);
		EventCameraPtr->SetEye(eye[3]);
		EventCameraPtr->SetAt(at);

		//�C�x���g�J������View�쐬
		_OpeningView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto OpeningCameraPtr = ObjectFactory::Create<OpeningCamera>();
		_OpeningView->SetCamera(OpeningCameraPtr);
		OpeningCameraPtr->SetEye(eye[3]);
		OpeningCameraPtr->SetAt(at);

		CreateSharedObjectGroup(L"StageObjects");
	}

	//�v���[���[�̍쐬
	void MainGameStage::CreatePlayer() 
	{
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");

		auto ptrPlayerMarker = AddGameObject<PlayerMarker>();
		ptrPlayerMarker->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerMarker", ptrPlayerMarker);

		auto ptrPlayerModel = AddGameObject<PlayerModel>();
		ptrPlayerModel->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerModel", ptrPlayerModel);
	}

	void MainGameStage::SettingObject()
	{
		auto MapFile = GameManager::GetManager()->GetXMLFilePath();
		auto PosKey = GameManager::GetManager()->GetLoadPosKey();
		//�Q�[���I�u�W�F�N�g�r���_�[
		GameObjecttXMLBuilder Builder;
		//�Q�[���I�u�W�F�N�g�̓o�^
		Builder.Register<StageObjectsLoopTex>(L"FixedGround");
		Builder.Register<StageObjects>(L"FixedObject");
		Builder.Register<LoadBlock>(L"LoadObject");
		Builder.Register<CommonBox>(L"CommonObject");
		Builder.Register<ActiveMovingObject>(L"MoveObject");
		Builder.Register<MovingObject>(L"PairObject");
		Builder.Register<SwitchObject>(L"SwitchObject");
		Builder.Register<EnemyCellMap>(L"EnemyCellMap");
		Builder.Register<ToyGuards>(L"Enemy");
		Builder.Register<CollectEnemy>(L"CollectEnemy");
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XML����Q�[���I�u�W�F�N�g�̍\�z
		wstring XMLStr = DataDir + L"ObjectData/" + MapFile;
		XMLStr += L".xml";
		Builder.Build(GetThis<Stage>(), XMLStr, L"root/Stage/StageObjects/Object");
		Builder.Build(GetThis<Stage>(), XMLStr, L"root/Stage/EnemyDatas/EnemyData");

		GameManager::GetManager()->SetSettingPosData(XMLStr);
		auto PlayerStart = GameManager::GetManager()->GetSettingPosData(PosKey);
		GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->SetPosition(PlayerStart);
	}

	void MainGameStage::SetMapCost()
	{
		//�Z���}�b�v����FixedBox�̏����Z�b�g
		auto PtrCellmapVec = GameManager::GetManager()->GetEnemyManager()->GetCellMapVec();
		auto StageGroup = GetSharedObjectGroup(L"StageObjects");
		for (auto &CellMap : PtrCellmapVec) {
			//�Z���}�b�v����Z���̔z����擾
			auto& CellVec = CellMap->GetCellVec();
			//�{�b�N�X�O���[�v����{�b�N�X�̔z����擾
			auto& BoxVec = StageGroup->GetGroupVector();
			vector<AABB> ObjectsAABBVec;
			for (auto& v : BoxVec) {
				auto FixedBoxPtr = dynamic_pointer_cast<StageObjects>(v.lock());
				if (FixedBoxPtr) {
					auto ColPtr = FixedBoxPtr->GetComponent<CollisionObb>();
					//�{�b�N�X�̏Փ˔��肩���b�s���O����AABB���擾���ĕۑ�
					ObjectsAABBVec.push_back(ColPtr->GetObb().GetWrappedAABB());
				}
			}
			//�Z���z�񂩂�Z�����X�L����
			for (auto& v : CellVec) {
				for (auto& v2 : v) {
					for (auto& vObj : ObjectsAABBVec) {
						if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange, vObj)) {
							//�{�b�N�X��ABB��NOT_EQUAL�ŏՓ˔���
							v2.m_Cost = -1;
							break;
						}
					}
				}
			}
		}
	}

	//������
	void MainGameStage::OnCreate()
	{
		try {
			StageBase::OnCreate();
			CreatePlayer();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//float PieceSize = 3.0f;
			//UINT mapSizeUint = 35;
			//auto Ptr = AddGameObject<StageCellMap>(Vec3(-49.5f, -0.5f, -46.5f), PieceSize, mapSizeUint, mapSizeUint, -1);
			//Ptr->SetDrawActive(false);
			SettingObject();
			//SetMapCost();
			//�X�J�C�{�b�N�X�쐬
			AddGameObject<CMeshBox>(Vec3(10, 10, 10), Vec3(0, 0, 0), Vec3(0, 0, 0), L"skybox_TX", L"SkyBox_MD");
			AddGameObject<EventCameraMan>();
			AddGameObject<OpeningCameraMan>();
			AddGameObject<GameMaskSprite>(L"clearmat_TX",L"LeafMat_TX",true);
			AddGameObject<DebugObj>();
			//BGM�̍Đ�
			auto AM = App::GetApp()->GetXAudio2Manager();
			m_CurrntBGM = AM->Start(L"MainBGM_SD", XAUDIO2_LOOP_INFINITE, 0.25f);

			//auto Vec = GetGameObjectVec();
			//for (auto C : Vec)
			//{
			//	auto Col = C->GetComponent<Collision>(false);
			//	if (Col)
			//	{
			//		Col->SetDrawActive(true);
			//	}
			//}
		}
		catch (...) {
			throw;
		}

	}

	//�X�V
	void MainGameStage::OnUpdate()
	{
		StageBase::OnUpdate();
		GameManager::GetManager()->OnUpdate();
		auto Dev = App::GetApp()->GetInputDevice().GetKeyState();
		if (Dev.m_bLastKeyTbl['G']&&!Test)
		{
			GameManager::GetManager()->SaveGameData();
			Test = true;
		}
	}

	//�`��
	void MainGameStage::OnDraw()
	{
		//���N���X
		StageBase::OnDraw();
	}

	void MainGameStage::OnDestroy()
	{
		//BGM��j��
		auto MAudio = App::GetApp()->GetXAudio2Manager();
		MAudio->Stop(m_CurrntBGM);
	}

	void MainGameStage::ToEventCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//ObjCamera�ɕύX
		auto ptrCameraman = GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		ptrCameraman->GetComponent<Transform>()->SetPosition(ptrMyCamera->GetEye());
		ptrCameraman->SetAtPos(ptrMyCamera->GetAt());
		auto ptrObjCamera = dynamic_pointer_cast<EventCamera>(_EventView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			//m_ObjCameraView���g��
			SetView(_EventView);
			_Camera = SelectCamera::pEventCamera;
		}
	}

	void MainGameStage::ToOpeningCamera()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//ObjCamera�ɕύX
		auto ptrCameraman = GetSharedGameObject<OpeningCameraMan>(L"OpeningCameraMan");
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		ptrCameraman->GetComponent<Transform>()->SetPosition(ptrMyCamera->GetEye());
		ptrCameraman->SetAt(ptrMyCamera->GetAt());
		auto ptrObjCamera = dynamic_pointer_cast<OpeningCamera>(_OpeningView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			//m_ObjCameraView���g��
			SetView(_OpeningView);
			_Camera = SelectCamera::pOpeningCamera;
		}
	}

	void MainGameStage::ToMyCamera()
	{
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		if (ptrMyCamera) {
			//m_MyCameraView���g��
			SetView(_MView);
			_Camera = SelectCamera::pMyCamera;
		}

	}

	//--------------------------------------------------------------------------------------
	//Movie�N���X
	//--------------------------------------------------------------------------------------
	//������
	void MyMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strMovie = dataDir + L"/Movies/" + L"PV.mp4";
		SetMovieFileName(strMovie);
		MovieStage::SetAutoRepeat(false);
		//�Đ�
		Play();
		GameManager::GetManager()->LoadStart();
	}

	void MyMovieStage::OnUpdate()
	{
		auto Input = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		
		if ((MovieStage::EndMedia()||Input.wPressedButtons == XINPUT_GAMEPAD_START)&GameManager::GetManager()->GetLoadEnd())
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

	//--------------------------------------------------------------------------------------
	//	TestStage�N���X����
	//--------------------------------------------------------------------------------------
	void TestStage::CreateViewLight() {
		const Vec3 eye[7] = { Vec3(0.0f, 5.0f, -5.0f),//�W���ʒu
							  Vec3(0.0f, 0.0f, -30.0f),
							  Vec3(0.0f, 20.0f, 00.1f),
							  Vec3(0.0f, 110.0f, -75.0f),
							  Vec3(0.0f,15.0f,50.0f),
							  Vec3(10.0f, 0.0f, -10.0f), 
								Vec3(0.0f,15.0f,-10.0f)};
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
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		//�J�����C���f�b�N�X
		_MyCameraIndex =_MView->AddView(Main,PtrCamera);
		PtrCamera->SetEye(eye[4]);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
		//�v���C���[�̏���n��
		auto ptrPlayer = GetSharedGameObject<PlayerMarker>(L"PlayerMarker");
		PtrCamera->SetTargetObject(ptrPlayer);
		PtrCamera->SetMinArm(1.0f);
		PtrCamera->SetMaxArm(50.0f);

		auto SubCamera = ObjectFactory::Create<Camera>();
		_SubCametaIndex=_MView->AddView(Sub, SubCamera);
		SubCamera->SetEye(eye[3]);
		SubCamera->SetAt(at);

		//�C�x���g�J������View�쐬
		_EventView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto EventCameraPtr = ObjectFactory::Create<EventCamera>();
		_EventView->SetCamera(EventCameraPtr);
		EventCameraPtr->SetEye(eye[3]);
		EventCameraPtr->SetAt(at);

	}

	void TestStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		ptrPlayer->GetComponent<Transform>()->SetPosition(-45, 5, -40);
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");

		auto ptrPlayerMarker = AddGameObject<PlayerMarker>();
		ptrPlayerMarker->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerMarker", ptrPlayerMarker);

		auto ptrPlayerModel = AddGameObject<PlayerModel>();
		ptrPlayerModel->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerModel", ptrPlayerModel);
	}
//�{�b�N�X�̍쐬
	void TestStage::CreateTilingFixedBox() {
		vector< vector<Vec3> > vec = {
			{
			Vec3(50.0f, 1.0f, 50.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f,0.5f,19.5f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f,0.5f,-19.5f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f,XM_PIDIV2,0.0f),
			Vec3(19.5f,0.5f,0.0f)
			},
			{
			Vec3(40.0f,1.0f,1.0f),
			Vec3(0.0f,XM_PIDIV2,0.0f),
			Vec3(-19.5f,0.5f,0.0f)
			},
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<TilingFixedBox>(v[0], v[1], v[2], 1.0f, 1.0f);
		}
	}

	//�Œ�̃{�b�N�X�̍쐬
	void TestStage::CreateFixedBox() {
		//�z��̏�����
		vector< vector<Vec3> > vec = {
			//{
			//	Vec3(50.0f, 1.0f, 50.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -0.5f, 0.0f)
			//},
			{
				Vec3(5.0f, 0.5f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(10.0f, 0.25f, 10.0f)
			},
			{
				Vec3(5.0f, 0.5f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(15.0f, 0.25f, 10.0f)
			},

			{
				Vec3(2.0f, 1.0f, 2.0f),
				Vec3(0, 0, 0),
				Vec3(10.0f, 0.5f, 10.0f)
			},
			{
				Vec3(4.0f, 1.0f, 4.0f),
				Vec3(0, 0, 0),
				Vec3(-10.0f, 0.5f, 10.0f)
			},
			{
				Vec3(10.0f, 0.5f, 10.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.25f, 10.0f)
			},
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<LoopTextureBox>(v[0],v[1], v[2], L"LeafMatB_TX", L"DEFAULT_CUBE");
		}
	}


	void TestStage::CreateCMeshBox() {
		vector< vector<Vec3> > vec = {
			//{
			//	Vec3(50.0f, 1.0f, 50.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -0.5f, 0.0f)
			//},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(10.0f, 0.25f, 10.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(15.0f, 0.25f, 10.0f)
			},

			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(10.0f, 0.5f, 10.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(-10.0f, 0.5f, 10.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.25f, 10.0f)
			},
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<CMeshBox>(v[0], v[1], v[2], L"RedApple_TX", L"Bridge_MD");
		}
	}

	void TestStage::CreateCommonBox() {
		vector< vector<Vec3> > vec = {
			//{
			//	Vec3(50.0f, 1.0f, 50.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -0.5f, 0.0f)
			//},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(17.0f, 0.5f, 2.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(17.0f, 0.5f, -4.0f)
			},

			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(17.0f, 0.5f, -10.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(17.0f, 0.5f, -16.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(17.0f, 0.5f, -22.0f)
			},
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<CommonBox>(v[0],v[1], v[2], L"LeafMatB_TX", L"Apple_MD");
		}
	}

	void TestStage::CreateStageObject()
	{
		auto test = CreateSharedObjectGroup(L"StageObjects");
		//�Q�[���I�u�W�F�N�g�r���_�[
		GameObjecttXMLBuilder Builder;
		//�Q�[���I�u�W�F�N�g�̓o�^
		Builder.Register<StageObjects>(L"FixedObject");
		Builder.Register<StageObjects>(L"BridgeObj");
		Builder.Register<StageObjects>(L"WarpObj");
		Builder.Register<ToyGuards>(L"Test");
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XML����Q�[���I�u�W�F�N�g�̍\�z
		wstring XMLStr = DataDir+L"ObjectData/" + L"NewMapTest";
		XMLStr += L".xml";
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage/StageObjects/Object");
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage/EnemyDatas/EnemyData");
	}

	//void TestStage::SetCellMapCost() {
	//	//�Z���}�b�v����FixedBox�̏����Z�b�g
	//	auto PtrCellmap = EnemyBase::GetCellMap().lock();
	//	auto StageGroup = GetSharedObjectGroup(L"StageObjects");
	//	//�Z���}�b�v����Z���̔z����擾
	//	auto& CellVec = PtrCellmap->GetCellVec();
	//	//�{�b�N�X�O���[�v����{�b�N�X�̔z����擾
	//	auto& BoxVec = StageGroup->GetGroupVector();
	//	vector<AABB> ObjectsAABBVec;
	//	for (auto& v : BoxVec) {
	//		auto FixedBoxPtr = dynamic_pointer_cast<StageObjects>(v.lock());
	//		if (FixedBoxPtr) {
	//			auto ColPtr = FixedBoxPtr->GetComponent<CollisionObb>();
	//			//�{�b�N�X�̏Փ˔��肩���b�s���O����AABB���擾���ĕۑ�
	//			ObjectsAABBVec.push_back(ColPtr->GetObb().GetWrappedAABB());
	//		}
	//	}
	//	//�Z���z�񂩂�Z�����X�L����
	//	for (auto& v : CellVec) {
	//		for (auto& v2 : v) {
	//			for (auto& vObj : ObjectsAABBVec) {
	//				if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange,vObj)) {
	//					//�{�b�N�X��ABB��NOT_EQUAL�ŏՓ˔���
	//					v2.m_Cost = 1;
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}

	void TestStage::OnCreate() {
		try {
			StageBase::OnCreate();
			//�r���[�ƃ��C�g�̍쐬
			SetPhysicsActive(true);
			CreatePlayer();
			CreateViewLight();
			//CreateFixedBox();
			//CreateTilingFixedBox();
			CreateCMeshBox();
			//CreateTilingFixedBox();
			CreateCommonBox();
			float PieceSize = 3.0f;
			UINT mapSizeUint = 35;
			auto Ptr = AddGameObject<StageCellMap>(Vec3(-49.5f, -0.5f, -46.5f), PieceSize, mapSizeUint, mapSizeUint,-1);
			Ptr->SetDrawActive(false);
			//EnemyBase::SetCellMap(Ptr);
			CreateStageObject();
			//SetCellMapCost();
			//AddGameObject<DebugObj>();
			
			//AddGameObject<GameMaskSprite>(L"clearmat_TX",L"LeafMat_TX",true);
			AddGameObject<MovingObject>();
			AddGameObject<SwitchObject>();
			AddGameObject<EventCameraMan>();

			//�X�J�C�{�b�N�X�쐬
			AddGameObject<CMeshBox>(Vec3(10,10,10), Vec3(0,0,0), Vec3(0,0,0), L"skybox_TX", L"SkyBox_MD");

			//AddGameObject<CBoneMeshBox>(Vec3(1, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 0),L"MITAGTV_MD");


		}
		catch (...) {
			throw;
		}
	}

	void TestStage::OnUpdate()
	{
		StageBase::OnUpdate();
	}

	void TestStage::ToEventCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//ObjCamera�ɕύX
		auto ptrCameraman = GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		ptrCameraman->GetComponent<Transform>()->SetPosition(ptrMyCamera->GetEye());
		ptrCameraman->SetAtPos(ptrMyCamera->GetAt());
		auto ptrObjCamera = dynamic_pointer_cast<EventCamera>(_EventView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			//m_ObjCameraView���g��
			SetView(_EventView);
			_Camera = SelectCamera::pEventCamera;
		}
	}

	void TestStage::ToMyCamera()
	{
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(_MView->GetCamera(_MyCameraIndex));
		if (ptrMyCamera) {
			//m_MyCameraView���g��
			SetView(_MView);
			_Camera = SelectCamera::pMyCamera;
		}

	}
}
//end basecross
