/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//�X�e�[�W�쐬�p�N���X
	StageObjects::StageObjects(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
		:GameObject(stage)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		//���b�V��
		_MeshKey = MeshStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Pos = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Scale
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScaleStr, L',');
		_Scal = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Rot
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		_TexKey = TexStr;
	}

	void StageObjects::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);
		auto MeshComp = DrawComp->GetMeshResource();
		//vector<VertexPositionColorTexture>& verteces = {};
		//DrawComp->SetDrawActive(false);

		AddTag(L"Obstacles");

		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);
		auto Group = GetStage()->GetSharedObjectGroup(L"StageObjects");
		Group->IntoGroup(GetThis<StageObjects>());
	}

	//------------------------------------------------------
	//SaveData
	//------------------------------------------------------
	SaveDataObject::SaveDataObject(const shared_ptr<Stage>&StagePtr, const wstring& SaveDataPath, const wstring& MeshKey, const wstring& TexKey,
		const Vec3 Pos, const Vec3 Scale, const Vec3 Rotation)
		:GameObject(StagePtr)
	{
		_Pos = Pos;
		_Scal = Scale;
		_Rot = Rotation;
		_MeshKey = MeshKey;
		_TexKey = TexKey;
		m_DataPath = SaveDataPath;
	}

	void SaveDataObject::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);

		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(false);
	}

	void SaveDataObject::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto PlayerPtr = dynamic_pointer_cast<Player>(other);
		if (PlayerPtr)
		{
			SendGameEvent(GetThis<GameEventInterface>(), L"LoadData", GameEventType::SaveDataIO);
		}
	}

	//
	StageObjectsLoopTex::StageObjectsLoopTex(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
		:StageObjects(stage, pNode)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		//���b�V��
		_MeshKey = MeshStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Pos = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Scale
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScaleStr, L',');
		_Scal = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Rot
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		_TexKey = TexStr;
	}

	void StageObjectsLoopTex::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);
		auto MeshComp = DrawComp->GetMeshResource();
		//vector<VertexPositionColorTexture>& verteces = {};
		//DrawComp->SetDrawActive(false);

		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);


		auto vert = MeshComp->GetBackupVerteces<VertexPositionNormalTexture>();
		for (int i = 0; i < vert.size(); i++)
		{
			auto v = vert[i].textureCoordinate;
			v.x *= _Scal.z;
			v.y *= _Scal.x;
			//v.y = PALSE * sinf((i + _cnt) / 20.0f);
			vert[i].textureCoordinate = v;
		}
		DrawComp->SetSamplerState(SamplerState::PointWrap);
		//_cnt++;
		DrawComp->UpdateVertices(vert);

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);
		//auto Group = GetStage()->GetSharedObjectGroup(L"StageObjects");
		//Group->IntoGroup(GetThis<StageObjects>());
	}


	//
	LoadBlock::LoadBlock(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
		:GameObject(stage)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		auto MapStr = XmlDocReader::GetAttribute(pNode, L"LoadMapFile");
		auto TargetPosStr = XmlDocReader::GetAttribute(pNode, L"TargetPosKey");
		//���b�V��
		_MeshKey = MeshStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Pos = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Scale
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScaleStr, L',');
		_Scal = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Rot
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		_TexKey = TexStr;

		_MapStr = MapStr;

		_TargetPosStr = TargetPosStr;
	}

	void LoadBlock::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);
		SetAlphaActive(true);

		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);

		GetStage()->SetSharedGameObject(L"Goal", GetThis<LoadBlock>());
	}

	void LoadBlock::OnUpdate()
	{
		auto PlayerObj = GetStage()->GetSharedGameObject<Player>(L"Player");
		if (PlayerObj->GetMoveActive()&&GameManager::GetManager()->CheckKeyVol())
		{
			AABB PVol = AABB(PlayerObj->GetComponent<Transform>()->GetPosition(), 1.0f, 1.0f, 1.0f);
			_SensingArea = AABB(GetComponent<Transform>()->GetPosition(), 2, 2, 2);
			if (HitTest::AABB_AABB(PVol, _SensingArea))
			{
				SendGameEvent(GetThis<GameEventInterface>(), _MapStr, GameEventType::MoveStage);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//���I�u�W�F�N�g�N���X(�X�C�b�`�ŉ�)
	//--------------------------------------------------------------------------------------
	MovingObject::MovingObject(const shared_ptr<Stage>&StagePtr, IXMLDOMNodePtr pNode)
		:GameObject(StagePtr), _MoveType(MovingType::Rotate),_OnEventFlag(false)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");
		auto LinkStr = XmlDocReader::GetAttribute(pNode, L"LINKCODE");
		auto MovingTypeStr = XmlDocReader::GetAttribute(pNode, L"MovingType");
		auto StartVecStr = XmlDocReader::GetAttribute(pNode, L"MoveStartVec");
		auto EndVecStr = XmlDocReader::GetAttribute(pNode, L"MoveEndVec");
		//���[�v���邩�ǂ����E

		//���[�V����Type
		_MoveType = (MovingType)_wtoi(MovingTypeStr.c_str());
		//���b�V��
		_MeshKey = MeshStr;
		//�e�N�X�`��
		_TexKey = TexStr;

		_LinkKey = LinkStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Position = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Scale
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScaleStr, L',');
		_Scale = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Rot
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rotate.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rotate.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rotate.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		Tokens.clear();
		Util::WStrToTokenVector(Tokens, StartVecStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Start = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);

		Tokens.clear();
		Util::WStrToTokenVector(Tokens, EndVecStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_End = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);

		//�I�u�W�F�N�g�p�����[�^
		//�p�����[�^�m�[�h
		//auto ParamNode = XmlDocReader::GetSelectSingleNode(pNode, L"ObjParam");
		_BeEnd = _End;
		_BeStart = _Start;
	}

	void MovingObject::OnCreate()
	{
		//�`��쐬
		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);
		DrawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawComp->SetEmissive(Col4(1, 1, 1, 1));
		SetAlphaActive(true);
		auto TransComp = AddComponent<Transform>();
		TransComp->SetPosition(_Position);
		TransComp->SetScale(_Scale);
		TransComp->SetRotation(_Rotate);

		auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);

		//�C�x���g���V�[�o�[�o�^
		App::GetApp()->GetEventDispatcher()->AddEventReceiverGroup(_LinkKey, GetThis<ObjectInterface>());
		GameManager::GetManager()->GetGameEventDispatcher()->AddEventReceiverGroup(_LinkKey, GetThis<GameEventInterface>());
	}

	void MovingObject::OnUpdate()
	{
		if (_OnEventFlag&& _EndFlag)
		{
			_OnEventFlag =!TestMove(5.0f);
		}
	}

	void MovingObject::OnEvent(const shared_ptr<Event>&event)
	{
		if (event->m_MsgStr == L"PushSwitch")
		{			
			//�X�C�b�`�������ꂽ!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;

			//auto ECO = GetTypeStage<StageBase>()->GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
			//SendEvent(GetThis<ObjectInterface>(), , L"EventStart");
			//SendEvent(GetThis<ObjectInterface>(), GameManager::GetManager()->GetThis<ObjectInterface>(), L"EventStart");
		}
		else if (event->m_MsgStr == L"Start")
		{
			//�X�C�b�`�������ꂽ!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;
		}
	}

	void MovingObject::OnGameEvent(const shared_ptr<GameEvent>&event)
	{
		if (event->m_MsgStr == L"PushSwitch")
		{
			//�X�C�b�`�������ꂽ!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;
			_EndFlag = false;
			//auto ECO = GetTypeStage<StageBase>()->GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
			//SendEvent(GetThis<ObjectInterface>(), , L"EventStart");
			//SendEvent(GetThis<ObjectInterface>(), GameManager::GetManager()->GetThis<ObjectInterface>(), L"EventStart");
		}
		else if (event->m_MsgStr == L"Start")
		{
			//�X�C�b�`�������ꂽ!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;
		}
	}

	bool MovingObject::TestMove(const float TotalTime)
	{
		_CurrntTime += App::GetApp()->GetElapsedTime();
		if (_CurrntTime > TotalTime) 
		{
			_EndFlag = true;
			_CurrntTime = 0.0f;
			return true;
		}
		Easing<Vec3> easing;
		auto Force = easing.EaseInOut(EasingType::Cubic, _Start, _End, _CurrntTime, TotalTime);
		auto ptrTrans = GetComponent<Transform>();
		switch (_MoveType)
		{
		case basecross::MovingObject::Position:
			ptrTrans->SetPosition(Force);
			break;
		case basecross::MovingObject::Scale:
			ptrTrans->SetScale(Force);
			break;
		case basecross::MovingObject::Rotate:
			const float LerpFact = 1.0f;
			bsm::Quat FQuat,NowQuat;
			NowQuat = ptrTrans->GetQuaternion();
			FQuat.rotationRollPitchYawFromVector(Force);
			FQuat.normalize();

			if (LerpFact >= 1.0f) {
				NowQuat = FQuat;
			}
			else {
				NowQuat = XMQuaternionSlerp(NowQuat, FQuat, LerpFact);
			}
			ptrTrans->SetQuaternion(NowQuat);
			break;
		}
		_EndFlag = false;
		return false;
	}

	//--------------------------------------------------------------------------------------
	//�X�C�b�`�N���X
	//--------------------------------------------------------------------------------------
	SwitchObject::SwitchObject(const shared_ptr<Stage>&stageptr, IXMLDOMNodePtr pNode)
		:GameObject(stageptr)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PositionStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotateStr = XmlDocReader::GetAttribute(pNode, L"Rot");
		auto RoopNode = XmlDocReader::GetAttribute(pNode, L"MovingType");
		auto LinkStr = XmlDocReader::GetAttribute(pNode, L"LINKCODE");

		_roop = (bool)_wtoi(RoopNode.c_str());
		_LinkKey = LinkStr;
		//���b�V��
		_MeshKey = MeshStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PositionStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Pos = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Scale
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScaleStr, L',');
		_Scal = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Rot
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotateStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		_TexKey = TexStr;

	}

	void SwitchObject::OnCreate()
	{
		//�`��쐬
		auto DrawComp = AddComponent<PNTStaticDraw>();
		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);

		auto TransComp = AddComponent<Transform>();
		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);

		auto Coll = AddComponent<CollisionObb>();
		//Coll->SetFixed(true);
	}

	void SwitchObject::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto Obj = dynamic_pointer_cast<Player>(other);
		if (Obj&&!_ActiveFlag)
		{
			//PostEvent(0.0f, GetThis<ObjectInterface>(), L"TESTEVENT",L"PushSwitch");
			_ActiveFlag = true;
			SendGameEvent(GetThis<GameEventInterface>(), _LinkKey, L"PushSwitch",GameEventType::GimmickAction);
		}
	}

	//--------------------------------------------------------------------------------------
	//�@�^�C�����O����Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	TilingFixedBox::TilingFixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		float UPic,
		float VPic
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_UPic(UPic),
		m_VPic(VPic)
	{}
	TilingFixedBox::~TilingFixedBox() {}
	//������
	void TilingFixedBox::OnCreate() {
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);
		auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float UCount = m_Scale.x / m_UPic;
		float VCount = m_Scale.z / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++) {
			if (vertices[i].textureCoordinate.x >= 1.0f) {
				vertices[i].textureCoordinate.x = UCount;
			}
			if (vertices[i].textureCoordinate.y >= 1.0f) {
				float FrontBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				float BackBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
				if (FrontBetween < 0.01f || BackBetween < 0.01f) {
					vertices[i].textureCoordinate.y = VCount;
				}
			}
		}
		//�`��R���|�[�l���g�̒ǉ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		PtrDraw->CreateOriginalMesh(vertices, indices);
		PtrDraw->SetOriginalMeshUse(true);
		PtrDraw->SetFogEnabled(true);
		//�����ɉe���f�肱�ނ悤�ɂ���
		PtrDraw->SetOwnShadowActive(true);
		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		PtrDraw->SetTextureResource(L"LeafMatB_TX");
		//�^�C�����O�ݒ�
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);

	}


	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	FixedBox::~FixedBox() {}

	//������
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"FixedBox");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"LeafMatB_TX");
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}
	//--------------------------------------------------------------------------------------
//	class CMeshBox : public GameObject;
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	CMeshBox::CMeshBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const wstring TexKey,
		const wstring MeshKey
		
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		_TexKey(TexKey),
		_MeshKey(MeshKey)
	{
	}
	CMeshBox::~CMeshBox() {}

	//������
	void CMeshBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"CMeshBox");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(_MeshKey);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(_MeshKey);
		ptrDraw->SetTextureResource(_TexKey);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}

	//--------------------------------------------------------------------------------------
//	class CMeshBox : public GameObject;
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	CBoneMeshBox::CBoneMeshBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const wstring MeshKey

	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		_MeshKey(MeshKey)
	{
	}
	CBoneMeshBox::~CBoneMeshBox() {}

	//������
	void CBoneMeshBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"CBoneMeshBox");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMultiMeshResource(_MeshKey);
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(_MeshKey);
		//ptrDraw->SetTextureResource(_TexKey);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}
	//--------------------------------------------------------------------------------------
//	class CommonBox : public GameObject;
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	CommonBox::CommonBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const wstring TexKey,
		const wstring MeshKey

	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		_TexKey(TexKey),
		_MeshKey(MeshKey),
		m_Tag(L"NULL")
	{
	}

	//Builder
	CommonBox::CommonBox(const shared_ptr<Stage>&StagePtr, IXMLDOMNodePtr Node)
		:GameObject(StagePtr)
	{
		auto PosStr = XmlDocReader::GetAttribute(Node, L"Pos");
		auto ScalStr = XmlDocReader::GetAttribute(Node, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(Node, L"Rot");
		auto MeshStr = XmlDocReader::GetAttribute(Node, L"MeshKey");
		auto TexKey = XmlDocReader::GetAttribute(Node, L"TexKey");
		auto TagName = XmlDocReader::GetAttribute(Node, L"Tag");

		//�g�[�N��
		vector<wstring> Tokens;
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		m_Position = Vec3((float)_wtof(Tokens[0].c_str()),
						  (float)_wtof(Tokens[1].c_str()),
						  (float)_wtof(Tokens[2].c_str()));

		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScalStr, L',');
		m_Scale = Vec3((float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str()));

		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotStr, L',');
		m_Rotation = Vec3((float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str()));

		//���b�V���E�e�N�X�`��Key
		_MeshKey = MeshStr;
		_TexKey = TexKey;
		m_Tag = TagName;
	}
	CommonBox::~CommonBox() {}

	//������
	void CommonBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(m_Tag);
		AddTag(L"Obstacles");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(_MeshKey);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(_MeshKey);
		ptrDraw->SetTextureResource(_TexKey);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->SetEmissive(Flt4(0.5f, 0.5f, 1.0f, 1));
	}

	//--------------------------------------------------------------------------------------
	//	class LoopTextureBox : public GameObject;
	//--------------------------------------------------------------------------------------
	LoopTextureBox::LoopTextureBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const wstring TexKey,
		const wstring MeshKey

	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		_TexKey(TexKey),
		_MeshKey(MeshKey)
	{}
	void LoopTextureBox::OnCreate()
	{


		auto DrawComp = AddComponent<AreaDraw>();
		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);
		DrawComp->SetDrawActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto mesh = DrawComp->GetMeshResource();
		auto vert = mesh->GetBackupVerteces<VertexPositionNormalTexture>();
		for (int i = 0; i < vert.size(); i++)
		{
			auto v = vert[i].position;
			v.x *= m_Scale.x;
			v.y *= m_Scale.z;
			//v.y = PALSE * sinf((i + _cnt) / 20.0f);
			vert[i].position = v;
		}
		//_cnt++;
		DrawComp->UpdateVertices(vert);

	}

	//-----------------------------------------------------------------
	//�I�[�v�j���O�J�����֌W
	//-----------------------------------------------------------------
	OpeningCameraMan::OpeningCameraMan(const shared_ptr<Stage>& StagePtr)
		:GameObject(StagePtr)
	{

	}

	OpeningCameraMan::~OpeningCameraMan(){}

	void OpeningCameraMan::OnCreate()
	{
		GetStage()->SetSharedGameObject(L"OpeningCameraMan", GetThis<OpeningCameraMan>());
		m_StateMachine.reset(new StateMachine<OpeningCameraMan>(GetThis<OpeningCameraMan>()));
		m_StateMachine->ChangeState(OPCMoveToGoal::Instance());
	}

	void OpeningCameraMan::OnUpdate()
	{
		m_StateMachine->Update();
	}

	void OpeningCameraMan::ToGoalParam()
	{
		auto CameraPtr = dynamic_pointer_cast<StageBase>(GetStage())->GetMyCamera();
		m_StartEye = CameraPtr->GetEye();
		m_StartAt = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
		m_EndAt = GetStage()->GetSharedGameObject<LoadBlock>(L"Goal")->GetComponent<Transform>()->GetPosition();
		m_EndEye = m_EndAt + (m_StartEye - m_StartAt)*1.0f;
		m_EndEye.y += 5.0f;
		m_CurrntAt = m_StartAt;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraMan::ToStartParam()
	{
		auto CameraPtr = dynamic_pointer_cast<StageBase>(GetStage())->GetMyCamera();
		auto Eye = m_EndEye;
		auto At = m_EndAt;
		m_StartEye = m_EndEye;
		m_StartAt = m_EndAt;
		m_EndAt = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
		m_EndEye = CameraPtr->GetEye();
		m_CurrntAt = m_StartAt;
		m_TotalTime = 0.0f;
	}
	
	bool OpeningCameraMan::Excute()
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > 5.0f) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartEye, m_EndEye, m_TotalTime, 5.0f);
		m_CurrntAt = easing.EaseInOut(EasingType::Cubic, m_StartAt, m_EndAt, m_TotalTime, 5.0f);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);

		return false;

	}

	//------------------------------------------------------
	//�I�[�v�j���O�J�����X�e�[�g
	//------------------------------------------------------
	//����
	IMPLEMENT_SINGLETON_INSTANCE(OPCMoveToGoal)
	void OPCMoveToGoal::Enter(const shared_ptr<OpeningCameraMan>&Obj)
	{
		Obj->ToGoalParam();
		Obj->GetTypeStage<MainGameStage>(false)->ToOpeningCamera();
	}

	void OPCMoveToGoal::Execute(const shared_ptr<OpeningCameraMan>&Obj)
	{
		if (Obj->Excute())
		{
			Obj->GetStateMachine()->ChangeState(OPCMoveToStart::Instance());
		}
	}

	void OPCMoveToGoal::Exit(const shared_ptr<OpeningCameraMan>&Obj)
	{

	}
	//
	IMPLEMENT_SINGLETON_INSTANCE(OPCMoveToStart)
	void OPCMoveToStart::Enter(const shared_ptr<OpeningCameraMan>&Obj)
	{
		Obj->ToStartParam();
	}

	void OPCMoveToStart::Execute(const shared_ptr<OpeningCameraMan>&Obj)
	{
		if (Obj->Excute())
		{
			Obj->GetTypeStage<MainGameStage>(false)->ToMyCamera();
			Obj->SetUpdateActive(false);
		}
	}

	void OPCMoveToStart::Exit(const shared_ptr<OpeningCameraMan>&Obj)
	{

	}

	//-----------------------------------------------------------------
	//�C�x���g�J�����}���N���X
	//-----------------------------------------------------------------
	void EventCameraMan::OnCreate()
	{
		_StateMachine.reset(new StateMachine<EventCameraMan>(GetThis<EventCameraMan>()));
		GetStage()->SetSharedGameObject(L"EventCameraMan", GetThis<EventCameraMan>());
		App::GetApp()->GetEventDispatcher()->AddEventReceiverGroup(L"EventCamera", GetThis<ObjectInterface>());
		GameManager::GetManager()->GetGameEventDispatcher()->AddEventCameraMan(GetThis<EventCameraMan>());
	}

	void EventCameraMan::OnUpdate()
	{
		auto ActiveCamera = GetTypeStage<StageBase>()->GetCameraSelects();
		if(ActiveCamera == SelectCamera::pEventCamera)
			_StateMachine->Update();
	}

	void EventCameraMan::OnEvent(const shared_ptr<Event>&event)
	{
		if (event->m_MsgStr == L"EventStart")
		{

		}
		else if (event->m_MsgStr == L"EventEnd")
		{

		}
	}

	//-------------------------------------------------------------------
	//�C�x���g�J�����X�e�[�g�}�V��
	//-------------------------------------------------------------------
	//�ҋ@
	IMPLEMENT_SINGLETON_INSTANCE(WaitState)
	//�J�n
	IMPLEMENT_SINGLETON_INSTANCE(MoveToEventPoint)
	void MoveToEventPoint::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//�s���N���X�Ƀp�����[�^��n��
		obj->GetBehavior<EventCameraBehavior>()->ToEventPointParam();
	}
	void MoveToEventPoint::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//�ړ����J�n����
		if (obj->GetBehavior<EventCameraBehavior>()->Execute())
		{
			obj->GetStateMachine()->ChangeState(EventExecute::Instance());
		}
	}
	void MoveToEventPoint::Exit(const shared_ptr<EventCameraMan>&obj)
	{
		//�p�����[�^�̒l���t���ɂ���
		//obj->GetBehavior<EventCameraBehavior>()->RevertParam();
		//�C�x���g���̃X�e�[�g�ɕς���
	}

	//�C�x���g��
	IMPLEMENT_SINGLETON_INSTANCE(EventExecute)
	void EventExecute::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//Manager�ɃC�x���g�n�_�ɂ������Ƃ�m�点��
		auto Event = obj->GetGameEvent();
		auto Receiver = Event->m_Receiver.lock();
		if (Receiver)
		{
			Receiver->OnGameEvent(Event);
		}

	}
	void EventExecute::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//�C�x���g�I���܂őҋ@
		//�I��������X�e�[�g��߂�
		if (obj->GetTargetObject().lock()->GetEventFlag())
		{
			obj->GetStateMachine()->ChangeState(MoveToStartPoint::Instance());
		}
	}
	void EventExecute::Exit(const shared_ptr<EventCameraMan>&obj)
	{

	}

	//�J�n
	IMPLEMENT_SINGLETON_INSTANCE(MoveToStartPoint)
	void MoveToStartPoint::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//�s���N���X�Ƀp�����[�^��n��
		obj->GetBehavior<EventCameraBehavior>()->ToStartPointParam();
	}
	void MoveToStartPoint::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//�ړ����J�n����
		if (obj->GetBehavior<EventCameraBehavior>()->Execute())
		{
			obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void MoveToStartPoint::Exit(const shared_ptr<EventCameraMan>&obj)
	{
		obj->GetTypeStage<MainGameStage>()->ToMyCamera();
	}

}
//end basecross
