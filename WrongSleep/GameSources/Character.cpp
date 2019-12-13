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
		//auto MeshStr = XmlDocReader::GetAttribute(pNode, L"Mesh");
		//auto TexStr = XmlDocReader::GetAttribute(pNode, L"Tex");
		auto PositionNode = XmlDocReader::GetSelectSingleNode(pNode, L"Pos");
		auto ScaleNode = XmlDocReader::GetSelectSingleNode(pNode, L"Scale");
		auto RotetaNode = XmlDocReader::GetSelectSingleNode(pNode, L"Rot");

		wstring PositionStr = XmlDocReader::GetText(PositionNode);
		wstring ScaleStr = XmlDocReader::GetText(ScaleNode);
		wstring RotetaStr = XmlDocReader::GetText(RotetaNode);

		//メッシュ
		//_MeshKey = MeshStr;

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
		Util::WStrToTokenVector(Tokens, RotetaStr, L',');
		//回転は「XM_PIDIV2」の文字列になっている場合がある
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

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);
		auto Group = GetStage()->GetSharedObjectGroup(L"StageObjects");
		Group->IntoGroup(GetThis<StageObjects>());
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

		//オブジェクトパラメータ
		//パラメータノード
		//auto ParamNode = XmlDocReader::GetSelectSingleNode(pNode, L"ObjParam");
	}

	void MovingObject::OnCreate()
	{
		//形状作成
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

		//イベントレシーバー登録
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
	//スイッチクラス
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
		//メッシュ
		//_MeshKey = MeshStr;

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
		Util::WStrToTokenVector(Tokens, RotetaStr, L',');
		//回転は「XM_PIDIV2」の文字列になっている場合がある
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		//_TexKey = TexStr;

	}

	void SwitchObject::OnCreate()
	{
		//形状作成
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
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
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
		_MeshKey(MeshKey)
	{
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
		AddTag(L"CommonBox");
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

	//-----------------------------------------------------------------
	//イベントカメラマンクラス
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
	//イベントカメラステートマシン
	//-------------------------------------------------------------------
	//開始
	IMPLEMENT_SINGLETON_INSTANCE(EventMove)
	void EventMove::Enter(const shared_ptr<EventCameraMan>&obj)
	{
		//行動クラスにパラメータを渡す
	}
	void EventMove::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//移動を開始する
		if (obj->GetBehavior<EventCameraBehavior>()->Move())
		{
			obj->GetStateMachine()->ChangeState(EventExecute::Instance());
		}
	}
	void EventMove::Exit(const shared_ptr<EventCameraMan>&obj)
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
	}
	void EventExecute::Execute(const shared_ptr<EventCameraMan>&obj)
	{
		//イベント終了まで待機
		//終了したらステートを戻す
	}
	void EventExecute::Exit(const shared_ptr<EventCameraMan>&obj)
	{

	}
}
//end basecross
