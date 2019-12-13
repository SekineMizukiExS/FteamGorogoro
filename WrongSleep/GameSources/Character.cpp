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
		//auto MeshStr = XmlDocReader::GetAttribute(pNode, L"Mesh");
		//auto TexStr = XmlDocReader::GetAttribute(pNode, L"Tex");
		auto PositionNode = XmlDocReader::GetSelectSingleNode(pNode, L"Pos");
		auto ScaleNode = XmlDocReader::GetSelectSingleNode(pNode, L"Scale");
		auto RotetaNode = XmlDocReader::GetSelectSingleNode(pNode, L"Rot");

		wstring PositionStr = XmlDocReader::GetText(PositionNode);
		wstring ScaleStr = XmlDocReader::GetText(ScaleNode);
		wstring RotetaStr = XmlDocReader::GetText(RotetaNode);

		//���b�V��
		//_MeshKey = MeshStr;

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
		Util::WStrToTokenVector(Tokens, RotetaStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		//_TexKey = TexStr;
	}

	void StageObjects::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		DrawComp->SetTextureResource(L"LeafMatB_TX");
		//DrawComp->SetDrawActive(false);

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

		//�I�u�W�F�N�g�p�����[�^
		//�p�����[�^�m�[�h
		//auto ParamNode = XmlDocReader::GetSelectSingleNode(pNode, L"ObjParam");
	}

	void MovingObject::OnCreate()
	{
		//�`��쐬
		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		DrawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawComp->SetEmissive(Col4(1, 1, 1, 1));

		auto TransComp = AddComponent<Transform>();
		TransComp->SetPosition(-15, 0, -12);
		TransComp->SetScale(35, 1, 5);
		TransComp->SetRotation(0, 0, 0);

		_Start = TransComp->GetScale();
		_End = Vec3(5, 1, 35);

		auto Coll = AddComponent<CollisionObb>();
		Coll->SetFixed(true);

		//�C�x���g���V�[�o�[�o�^
		App::GetApp()->GetEventDispatcher()->AddEventReceiverGroup(L"TESTEVENT", GetThis<ObjectInterface>());
	}

	void MovingObject::OnUpdate()
	{
		if (_OnEventFlag)
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

	bool MovingObject::TestMove(const float TotalTime)
	{
		_CurrntTime += App::GetApp()->GetElapsedTime();
		if (_CurrntTime > TotalTime) 
		{
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
		return false;
	}

	//--------------------------------------------------------------------------------------
	//�X�C�b�`�N���X
	//--------------------------------------------------------------------------------------
	SwitchObject::SwitchObject(const shared_ptr<Stage>&stageptr, IXMLDOMNodePtr pNode)
		:GameObject(stageptr)
	{
		//auto MeshStr = XmlDocReader::GetAttribute(pNode, L"Mesh");
		//auto TexStr = XmlDocReader::GetAttribute(pNode, L"Tex");
		auto PositionNode = XmlDocReader::GetSelectSingleNode(pNode, L"Pos");
		auto ScaleNode = XmlDocReader::GetSelectSingleNode(pNode, L"Scale");
		auto RotetaNode = XmlDocReader::GetSelectSingleNode(pNode, L"Rot");
		auto RoopNode = XmlDocReader::GetAttribute(pNode, L"IsRoop");
		auto LinkStr = XmlDocReader::GetAttribute(pNode, L"LINKCODE");

		wstring PositionStr = XmlDocReader::GetText(PositionNode);
		wstring ScaleStr = XmlDocReader::GetText(ScaleNode);
		wstring RotetaStr = XmlDocReader::GetText(RotetaNode);

		_roop = (bool)_wtoi(RoopNode.c_str());
		_LinkKey = LinkStr;
		//���b�V��
		//_MeshKey = MeshStr;

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
		Util::WStrToTokenVector(Tokens, RotetaStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		//_TexKey = TexStr;

	}

	void SwitchObject::OnCreate()
	{
		//�`��쐬
		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		DrawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		DrawComp->SetEmissive(Col4(1, 0, 0, 1));

		auto TransComp = AddComponent<Transform>();
		TransComp->SetPosition(-30, 0.5, -40);
		TransComp->SetScale(1, 1, 1);
		TransComp->SetRotation(0, 0, 0);

		auto Coll = AddComponent<CollisionObb>();
		//Coll->SetFixed(true);
	}

	void SwitchObject::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto Obj = dynamic_pointer_cast<Player>(other);
		if (Obj)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), L"TESTEVENT",L"PushSwitch");
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
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
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
		_MeshKey(MeshKey)
	{
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
		AddTag(L"CommonBox");
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

	//-----------------------------------------------------------------
	//�C�x���g�J�����}���N���X
	//-----------------------------------------------------------------
	void EventCameraMan::OnCreate()
	{
		_StateMachine.reset(new StateMachine<EventCameraMan>(GetThis<EventCameraMan>()));
		GetStage()->SetSharedGameObject(L"EventCameraMan", GetThis<EventCameraMan>());
		App::GetApp()->GetEventDispatcher()->AddEventReceiverGroup(L"EventCamera", GetThis<ObjectInterface>());
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
			_StateMachine->ChangeState(EventMove::Instance());
		}
		else if (event->m_MsgStr == L"EventEnd")
		{
			_StateMachine->ChangeState(EventMove::Instance());
		}
	}

	//-------------------------------------------------------------------
	//�C�x���g�J�����X�e�[�g�}�V��
	//-------------------------------------------------------------------
	//�J�n
	IMPLEMENT_SINGLETON_INSTANCE(EventMove)
	void EventMove::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//�s���N���X�Ƀp�����[�^��n��
	}
	void EventMove::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//�ړ����J�n����
		if (obj->GetBehavior<EventCameraBehavior>()->Move())
		{
			obj->GetStateMachine()->ChangeState(EventExecute::Instance());
		}
	}
	void EventMove::Exit(const shared_ptr<EventCameraMan>&obj)
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
	}
	void EventExecute::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//�C�x���g�I���܂őҋ@
		//�I��������X�e�[�g��߂�
	}
	void EventExecute::Exit(const shared_ptr<EventCameraMan>&obj)
	{

	}
}
//end basecross
