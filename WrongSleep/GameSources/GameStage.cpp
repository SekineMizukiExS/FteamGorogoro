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
		GameManager::CreateManager(GetThis<StageBase>());
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
		GameManager::DeleteManager();
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
	void StartStage::CreateViewLight()
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

	void StartStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//AddGameObject<TitleUI>(1280, 800, Vec2(0, 0), 0, L"Test_TX");
		}
		catch (...) {
			throw;
		}
	}

	void StartStage::OnUpdate()
	{
		auto Dev = App::GetApp()->GetInputDevice().GetKeyState();
		if (Dev.m_bLastKeyTbl['S'])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTestStage");
		}
	}

	//!endStartStage

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
		_MView->AddView(Main,PtrCamera);
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
		PtrCamera->SetMaxArm(20.0f);

		auto SubCamera = ObjectFactory::Create<Camera>();
		_MView->AddView(Sub, SubCamera);
		SubCamera->SetEye(eye[3]);
		SubCamera->SetAt(at);

	}

	void TestStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");

		auto ptrPlayerMarker = AddGameObject<PlayerMarker>();
		ptrPlayerMarker->SetTargetObject(ptrPlayer);
		SetSharedGameObject(L"PlayerMarker", ptrPlayerMarker);
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
			AddGameObject<FixedBox>(v[0], v[1], v[2]);
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
			AddGameObject<CMeshBox>(v[0], v[1], v[2], L"RedApple_TX", L"Apple_MD");
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
				Vec3(10.0f, 0.5f, 3.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(15.0f, 0.5f, 2.0f)
			},

			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(10.0f, 0.5f, 1.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0, 0, 0),
				Vec3(-10.0f, 0.5f, -5.0f)
			},
			{
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(-0.5f, 0.0f, -0.5f),
				Vec3(-10.0f, 0.5f, -3.0f)
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
		Builder.Register<ToyGuards>(L"Test");
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XML����Q�[���I�u�W�F�N�g�̍\�z
		wstring XMLStr = DataDir+L"ObjectData/" + L"MapTestVer5";
		XMLStr += L".xml";
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage/StageObjects/Object");
		Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage/EnemyDatas/EnemyData");
	}

	//void TestStage::ToMyCamera() {
	//	auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
	//	//MyCamera�ɕύX
	//	auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
	//	if (ptrMyCamera) {
	//		ptrMyCamera->SetTargetObject(ptrPlayer);
	//		//m_MyCameraView���g��
	//		//SetView(m_MyCameraView);
	//		//m_CameraSelect = CameraSelect::myCamera;

	//	}
	//}

	void TestStage::SetCellMapCost() {
		//�Z���}�b�v����FixedBox�̏����Z�b�g
		auto PtrCellmap = EnemyBase::GetCellMap().lock();
		auto StageGroup = GetSharedObjectGroup(L"StageObjects");
		//�Z���}�b�v����Z���̔z����擾
		auto& CellVec = PtrCellmap->GetCellVec();
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
					if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange,vObj)) {
						//�{�b�N�X��ABB��NOT_EQUAL�ŏՓ˔���
						v2.m_Cost = 1;
						break;
					}
				}
			}
		}
	}

	void TestStage::OnCreate() {
		try {
			StageBase::OnCreate();
			//�r���[�ƃ��C�g�̍쐬
			SetPhysicsActive(true);
			CreatePlayer();
			CreateViewLight();
			//CreateFixedBox();
			//CreateTilingFixedBox();
			//CreateCMeshBox();
			//CreateTilingFixedBox();
			CreateCommonBox();
			float PieceSize = 3.0f;
			UINT mapSizeUint = 35;
			auto Ptr = AddGameObject<StageCellMap>(Vec3(-49.5f, -0.5f, -46.5f), PieceSize, mapSizeUint, mapSizeUint,-1);
			Ptr->SetDrawActive(true);
			EnemyBase::SetCellMap(Ptr);
			CreateStageObject();
			SetCellMapCost();
			//AddGameObject<DebugObj>();
			
			AddGameObject<MovingObject>();
			AddGameObject<SwitchObject>();

			//�X�J�C�{�b�N�X�쐬
			//AddGameObject<CMeshBox>(Vec3(10,10,10), Vec3(0,0,0), Vec3(0,0,0), L"skybox_TX", L"SkyBox_MD");

			//AddGameObject<CBoneMeshBox>(Vec3(1, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 0),L"MITAGTV_MD");

			//_Ts= AddGameObject<Futon>();
			//AddGameObject<Futon>();
			//Test
			//GameObjecttXMLBuilder Builder;
			////�Q�[���I�u�W�F�N�g�̓o�^
			//Builder.Register<ToyGuards>(L"Test");
			//wstring DataDir;
			//App::GetApp()->GetDataDirectory(DataDir);
			////XML����Q�[���I�u�W�F�N�g�̍\�z
			//wstring XMLStr = DataDir + L"ObjectData/" + L"TestEnemy";
			//XMLStr += L".xml";
			//shared_ptr<EnemyManager> test;
			//Builder.Build(GetThis<TestStage>(), XMLStr, L"root/Stage1/InitObject/GameObject");			 

			//ToMyCamera();
		}
		catch (...) {
			throw;
		}
	}


	void TestStage::OnUpdate()
	{
		StageBase::OnUpdate();

		auto Dev = App::GetApp()->GetInputDevice().GetKeyState();
		if (Dev.m_bLastKeyTbl['S'])
		{
			//m_EfkPlay = ObjectFactory::Create<EfkPlay>(L"TestEfk", Vec3(0, 1, 0));
			//EfkPlay(L"TestEfk",Vec3(0, 1, 0));
			//PostEvent(1.0f, GetThis<ObjectInterface>(), _Ts, L"StopFuton");
		}
		if (Dev.m_bLastKeyTbl['W'])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), _Ts, L"StartFuton");
		}
		StageBase::OnUpdate();
		
	}
}
//end basecross
