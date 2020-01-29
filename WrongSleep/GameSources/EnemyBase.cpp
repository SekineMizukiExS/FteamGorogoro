#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//前方定義
	class GameManager;
	class EnemyBase;
	//------------------------------------------------------
	//Enemyセルマップ
	//------------------------------------------------------
	EnemyCellMap::EnemyCellMap(const shared_ptr<Stage>&StagePtr, IXMLDOMNodePtr pNode)
		:StageCellMap(StagePtr)
	{
		auto MapKeyStr = XmlDocReader::GetAttribute(pNode, L"MapKey");
		auto MiniPosStr = XmlDocReader::GetAttribute(pNode, L"MiniPos");
		auto PieceSizeStr = XmlDocReader::GetAttribute(pNode, L"PieceSize");
		auto PieceCountXStr = XmlDocReader::GetAttribute(pNode, L"PieceCountX");
		auto PieceCountZStr = XmlDocReader::GetAttribute(pNode, L"PieceCountZ");
		auto DefaultCostStr = XmlDocReader::GetAttribute(pNode, L"DefaultCost");

		m_MapKey = MapKeyStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, MiniPosStr, L',');
		//各トークン（カラム）を読み込む
		m_MiniPos = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);

		m_PieceSize = (float)_wtof(PieceSizeStr.c_str());

		m_PieceCountX = (UINT)_wtoi(PieceCountXStr.c_str());

		m_PieceCountZ = (UINT)_wtoi(PieceCountZStr.c_str());

		m_DefaultCost = (int)_wtoi(DefaultCostStr.c_str());
	}

	void EnemyCellMap::OnCreate()
	{
		StageCellMap::CreateCellMap(m_MiniPos, m_PieceSize, m_PieceCountX, m_PieceCountZ, m_DefaultCost);

		StageCellMap::OnCreate();
		SetDrawActive(true);

		GameManager::GetManager()->GetEnemyManager()->AddCellMap(m_MapKey, GetThis<EnemyCellMap>());
	}
	//----------------------------------------
	///エネミー管理クラス
	//----------------------------------------
	struct EnemyManager::Impl
	{
		//ステージセルマップ
		map<wstring, shared_ptr<EnemyCellMap>> m_MapList;

		Impl()
		{
			m_MapList.clear();
		}
		~Impl() {}

		void SetCellMapData(const wstring& Key, const shared_ptr<EnemyCellMap> CellMap)
		{
			m_MapList[Key] = CellMap;
		}

		shared_ptr<EnemyCellMap> GetCellMapData(const wstring& Key) { return m_MapList[Key]; }

		vector<shared_ptr<EnemyCellMap>> GetCellMapVec();

		bool ChackIntoTarget(const AABB& targetPosition, shared_ptr<EnemyCellMap>&Out);
	};

	vector<shared_ptr<EnemyCellMap>> EnemyManager::Impl::GetCellMapVec()
	{
		vector<shared_ptr<EnemyCellMap>> resultVec;
		resultVec.clear();
		auto begin = m_MapList.begin();
		auto end = m_MapList.end();
		for (begin; begin != end; begin++)
		{
			resultVec.push_back(begin->second);
		}

		return resultVec;
	}

	bool EnemyManager::Impl::ChackIntoTarget(const AABB& targetVol,shared_ptr<EnemyCellMap>&Out)
	{
		for (auto CellMap :m_MapList)
		{
			AABB MapVol;
			CellMap.second->GetMapAABB(MapVol);
			//マップに目標がいたら
			if (HitTest::AABB_AABB(MapVol, targetVol))
			{
				Out = CellMap.second;
				return true;
			}
		}
		return false;
	}

	EnemyManager::EnemyManager()
		:pImpl(make_unique<Impl>())
	{

	}

	EnemyManager::~EnemyManager()
	{}

	void EnemyManager::AddCellMap(const wstring&Key, const shared_ptr<EnemyCellMap>&CellMap)
	{
		pImpl->SetCellMapData(Key, CellMap);
	}

	weak_ptr<EnemyCellMap> EnemyManager::GetCellMap(const wstring& MapKey)
	{
		return pImpl->GetCellMapData(MapKey);
	}

	vector<shared_ptr<EnemyCellMap>> EnemyManager::GetCellMapVec()
	{
		return pImpl->GetCellMapVec();
	}

	void EnemyManager::OnEvent(const shared_ptr<Event>&event)
	{

	}
	//----------------------------------------
	//EnemyBase::Impl
	//----------------------------------------
	//struct EnemyParam
	//{
	//	//Position
	//	Vec3 _Position;
	//	//Scale
	//	Vec3 _Scale;
	//	//Rotate
	//	Vec3 _Rotate;
	//	//TexKey
	//	wstring _TexKey;
	//	//MeshKey
	//	wstring _MeshKey;
	//	//エネミーの状態＜巡回・追跡・索敵＞
	//	enum State
	//	{
	//		Wait,//停止
	//		Traveling,//巡回
	//		Tracking,//追跡
	//		Search//捜索
	//	};
	//	//状態メンバ変数<=ゲームマネージャーから使う
	//	State _state;
	//	//識別コード (オブジェクトクラス名)-(継承クラス名)-(個別番号)
	//	//wstring _CODE;
	//	//巡回経路
	//	map<int,Vec3> TravelingPoint;
	//	//捜索範囲
	//	float _Distance;
	//	//追跡対象
	//	shared_ptr<GameObject> _TargetObj;

	//	EnemyParam()
	//		:_state(State::Traveling), _TargetObj(nullptr)
	//	{

	//	}
	//	~EnemyParam() {}
	//	//一番近い巡回経路を返す
	//	//const Vec3 GetNearPoint(const Vec3 &CurrentPosition)const
	//	//{

	//	//}
	//			
	//};

	//-------------------------------------------
	//Enemyクラスの実装
	//-------------------------------------------
	//Static変数の実体
	EnemyBase::EnemyBase(const shared_ptr<Stage>&Stage)
		:GameObject(Stage)
	{

	}

	EnemyBase::EnemyBase(const shared_ptr<Stage>&Stage, IXMLDOMNodePtr pNode)
		:GameObject(Stage)
	{
		auto MapKeyStr = XmlDocReader::GetAttribute(pNode, L"MapKey");
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		//マップキー
		m_MapKey = MapKeyStr;
		//メッシュ
		_MeshKey = MeshStr;
		//テクスチャ
		_TexKey = TexStr;

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

		
		//巡回ポジションノード
		auto MovePNode = XmlDocReader::GetSelectSingleNode(pNode, L"MovePoint");
		auto PointNodes = XmlDocReader::GetSelectSingleNode(MovePNode, L"Point");
		auto POINTDATANODE = XmlDocReader::GetSelectNodes(PointNodes, L"POINTDATA");
		auto PNCount = XmlDocReader::GetLength(POINTDATANODE);
		for (int i = 0; i < PNCount; i++)
		{
			auto PointNode = XmlDocReader::GetItem(POINTDATANODE, i);
			auto PointStr = XmlDocReader::GetAttribute(PointNode, L"Pos");
			auto PointBStr = XmlDocReader::GetAttribute(PointNode, L"TravelingB");
			auto PointAStr = XmlDocReader::GetAttribute(PointNode, L"TravelingA");
			Tokens.clear();
			Util::WStrToTokenVector(Tokens, PointStr, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			auto Point = Vec3(
				(float)_wtof(Tokens[0].c_str()),
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str())
			);

			auto B = (int)_wtoi(PointBStr.c_str());
			auto A = (int)_wtoi(PointAStr.c_str());

			TravelingPoint temp(B, Point, A);

			_TravelingPoint.push_back(temp);
		}

	}
	void EnemyBase::OnEvent(const shared_ptr<Event> &event)
	{
		if (event->m_MsgStr == L"SelectButton")
		{
			auto Active = GetUpdateActive();
			SetUpdateActive(!Active);
		}
	}

	void EnemyBase::OnDestroy()
	{
		SendEvent(GetThis<ObjectInterface>(), L"EnemyManager", L"OnDestroy");
		GetStage()->RemoveGameObject<EnemyBase>(GetThis<EnemyBase>());
	}

	//-------------------------------------------
	//Enemyステートマシン実装
	//-------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(TravelingState);
    void TravelingState::Enter(const shared_ptr<EnemyBase>&obj)
	{
		//前回位置がある場合その場所を最初のPointに設定
		//現在地点か一番近いPointを取得
		//obj->GetBehavior<EnemyBehavior>()->SetPositon(obj->GetComponent<Transform>()->GetPosition());
		obj->GetBehavior<EnemyBehavior>()->SetNextPoint();
	}

	void TravelingState::Execute(const shared_ptr<EnemyBase>&obj)
	{
		//巡回経路を取得
		if (obj->GetBehavior<EnemyBehavior>()->TravelingMove())
		{
			//到達したら次の地点を取得
			obj->GetBehavior<EnemyBehavior>()->SetNextPoint();
		}
	}

	void TravelingState::Exit(const shared_ptr<EnemyBase>&Obj)
	{
		//状態遷移時の位置座標を保持
	}

	//
	IMPLEMENT_SINGLETON_INSTANCE(TrackingState);
	void TrackingState::Enter(const shared_ptr<EnemyBase>&obj)
	{
		//前回位置がある場合その場所を最初のPointに設定
		//現在地点か一番近いPointを取得
		auto Temp = obj->GetStage()->GetSharedGameObject<Player>(L"Player");
		obj->GetBehavior<EnemyBehavior>()->SetTargetObject(Temp);

	}

	void TrackingState::Execute(const shared_ptr<EnemyBase>&obj)
	{
		//巡回経路を取得
		if (obj->GetBehavior<EnemyBehavior>()->TrackingMove())
		{
			obj->GetStateMachine()->ChangeState(TravelingState::Instance());
		}
	}

	void TrackingState::Exit(const shared_ptr<EnemyBase>&obj)
	{
		//ターゲット情報を破棄
		obj->GetBehavior<EnemyBehavior>()->SetTargetObject(nullptr);
	}


	//------------------------------------------------------------------
	//
	//------------------------------------------------------------------
	void ToyGuards::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);

		TransComp->SetPosition(_Position);
		TransComp->SetScale(_Scale);
		TransComp->SetRotation(_Rotate);

		m_SteteMachine.reset(new StateMachine<EnemyBase>(GetThis<ToyGuards>()));

		m_SteteMachine->ChangeState(TravelingState::Instance());

		//経路探索
		auto MapPtr = GetCellMap().lock();
		if (MapPtr)
		{
			AddComponent<PathSearch>(MapPtr);
		}
		else
		{
			throw BaseException(
				L"CellMapがありません",
				L"Enemy.cpp",
				L"EnemyBase::OnCreate()"
			);
		}
		
		AddComponent<CollisionObb>();

		AddComponent<Gravity>();
	}

	void ToyGuards::OnUpdate()
	{
		if (GetTypeStage<StageBase>()->GetCameraSelects() == SelectCamera::pEventCamera)
			return;

		m_SteteMachine->Update();

		auto Dev = App::GetApp()->GetInputDevice().GetKeyState();
		if (Dev.m_bLastKeyTbl['B'])
		{
			m_SteteMachine->ChangeState(TrackingState::Instance());
		}

		//落下したら削除


	}
}