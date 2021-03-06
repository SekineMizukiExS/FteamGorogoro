/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//ステージ作成用クラス
	StageObjects::StageObjects(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
		:GameObject(stage)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		//メッシュ
		_MeshKey = MeshStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		//回転は「XM_PIDIV2」の文字列になっている場合がある
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

		//CollisionSphere衝突判定を付ける
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

		//メッシュ
		_MeshKey = MeshStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		//回転は「XM_PIDIV2」の文字列になっている場合がある
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

		//CollisionSphere衝突判定を付ける
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
		//メッシュ
		_MeshKey = MeshStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		//回転は「XM_PIDIV2」の文字列になっている場合がある
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
	//可動オブジェクトクラス(スイッチで可動)
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
		//ループするかどうか・

		//モーションType
		_MoveType = (MovingType)_wtoi(MovingTypeStr.c_str());
		//メッシュ
		_MeshKey = MeshStr;
		//テクスチャ
		_TexKey = TexStr;

		_LinkKey = LinkStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		//回転は「XM_PIDIV2」の文字列になっている場合がある
		_Rotate.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rotate.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rotate.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		Tokens.clear();
		Util::WStrToTokenVector(Tokens, StartVecStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
		_Start = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);

		Tokens.clear();
		Util::WStrToTokenVector(Tokens, EndVecStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
		_End = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);

		//オブジェクトパラメータ
		//パラメータノード
		//auto ParamNode = XmlDocReader::GetSelectSingleNode(pNode, L"ObjParam");
		_BeEnd = _End;
		_BeStart = _Start;
	}

	void MovingObject::OnCreate()
	{
		//形状作成
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

		//イベントレシーバー登録
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
			//スイッチが押された!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;

			//auto ECO = GetTypeStage<StageBase>()->GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
			//SendEvent(GetThis<ObjectInterface>(), , L"EventStart");
			//SendEvent(GetThis<ObjectInterface>(), GameManager::GetManager()->GetThis<ObjectInterface>(), L"EventStart");
		}
		else if (event->m_MsgStr == L"Start")
		{
			//スイッチが押された!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;
		}
	}

	void MovingObject::OnGameEvent(const shared_ptr<GameEvent>&event)
	{
		if (event->m_MsgStr == L"PushSwitch")
		{
			//スイッチが押された!
			_OnEventFlag = _OnEventFlag ? true : !_OnEventFlag;
			_EndFlag = false;
			//auto ECO = GetTypeStage<StageBase>()->GetSharedGameObject<EventCameraMan>(L"EventCameraMan");
			//SendEvent(GetThis<ObjectInterface>(), , L"EventStart");
			//SendEvent(GetThis<ObjectInterface>(), GameManager::GetManager()->GetThis<ObjectInterface>(), L"EventStart");
		}
		else if (event->m_MsgStr == L"Start")
		{
			//スイッチが押された!
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
		//auto Force = easing.EaseInOut(EasingType::Cubic, _Start, _End, _CurrntTime, TotalTime);
		auto Force = easing.Linear(_Start,_End,_CurrntTime,TotalTime);
		auto ptrTrans = GetComponent<Transform>();
		_Force = Force - ptrTrans->GetPosition();
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
	//スイッチクラス
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
		//メッシュ
		_MeshKey = MeshStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PositionStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		//回転は「XM_PIDIV2」の文字列になっている場合がある
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		_TexKey = TexStr;

	}

	void SwitchObject::OnCreate()
	{
		//形状作成
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
	//　タイリングする固定のボックス
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
	//初期化
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
		//描画コンポーネントの追加
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		PtrDraw->CreateOriginalMesh(vertices, indices);
		PtrDraw->SetOriginalMeshUse(true);
		PtrDraw->SetFogEnabled(true);
		//自分に影が映りこむようにする
		PtrDraw->SetOwnShadowActive(true);
		//描画コンポーネントテクスチャの設定
		PtrDraw->SetTextureResource(L"LeafMatB_TX");
		//タイリング設定
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);

	}


	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
//構築と破棄
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

	//初期化
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
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
//構築と破棄
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

	//初期化
	void CMeshBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"CMeshBox");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
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
//構築と破棄
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

	//初期化
	void CBoneMeshBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"CBoneMeshBox");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
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
//構築と破棄
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

		//トークン
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

		//メッシュ・テクスチャKey
		_MeshKey = MeshStr;
		_TexKey = TexKey;
		m_Tag = TagName;
	}
	CommonBox::~CommonBox() {}

	//初期化
	void CommonBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(m_Tag);
		AddTag(L"Obstacles");
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
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

		//OBB衝突j判定を付ける
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
	//オープニングカメラ関係
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
	//オープニングカメラステート
	//------------------------------------------------------
	//動く
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
	//イベントカメラマンクラス
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
	//イベントカメラステートマシン
	//-------------------------------------------------------------------
	//待機
	IMPLEMENT_SINGLETON_INSTANCE(WaitState)
	//開始
	IMPLEMENT_SINGLETON_INSTANCE(MoveToEventPoint)
	void MoveToEventPoint::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//行動クラスにパラメータを渡す
		obj->GetBehavior<EventCameraBehavior>()->ToEventPointParam();
	}
	void MoveToEventPoint::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//移動を開始する
		if (obj->GetBehavior<EventCameraBehavior>()->Execute())
		{
			obj->GetStateMachine()->ChangeState(EventExecute::Instance());
		}
	}
	void MoveToEventPoint::Exit(const shared_ptr<EventCameraMan>&obj)
	{
		//パラメータの値を逆順にする
		//obj->GetBehavior<EventCameraBehavior>()->RevertParam();
		//イベント中のステートに変える
	}

	//イベント中
	IMPLEMENT_SINGLETON_INSTANCE(EventExecute)
	void EventExecute::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//Managerにイベント地点についたことを知らせる
		auto Event = obj->GetGameEvent();
		auto Receiver = Event->m_Receiver.lock();
		if (Receiver)
		{
			Receiver->OnGameEvent(Event);
		}

	}
	void EventExecute::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//イベント終了まで待機
		//終了したらステートを戻す
		if (obj->GetTargetObject().lock()->GetEventFlag())
		{
			obj->GetStateMachine()->ChangeState(MoveToStartPoint::Instance());
		}
	}
	void EventExecute::Exit(const shared_ptr<EventCameraMan>&obj)
	{

	}

	//開始
	IMPLEMENT_SINGLETON_INSTANCE(MoveToStartPoint)
	void MoveToStartPoint::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//行動クラスにパラメータを渡す
		obj->GetBehavior<EventCameraBehavior>()->ToStartPointParam();
	}
	void MoveToStartPoint::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//移動を開始する
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
