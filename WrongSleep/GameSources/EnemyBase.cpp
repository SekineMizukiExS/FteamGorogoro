#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//前方定義
	class EnemyBase;

	//----------------------------------------
	///エネミー管理クラス
	//----------------------------------------
	EnemyManager::EnemyManager()
	{

	}
	
	void EnemyManager::GenerateEnemyObject(const shared_ptr<Stage>& TargetStage, const wstring &EnemyDataPath)
	{
		//XMLファイルの読込
	}

	void EnemyManager::OnEvent(const shared_ptr<Event>&event)
	{

	}

	//----------------------------------------
	///
	//----------------------------------------
	//--------------------------------------------------------------------------------------
	//	struct GameObjecttXMLBuilder::Impl;
	//	用途: Implイディオム
	//--------------------------------------------------------------------------------------
	struct EnemyXMLBuilder::Impl{
		map<wstring, shared_ptr<EnemyXMLCreatorBase> > m_CreatorMap;
		Impl()
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//エネミー専用ビルダークラス
	//--------------------------------------------------------------------------------------

	EnemyXMLBuilder::EnemyXMLBuilder() :
		pImpl(new Impl())
	{

	}
	EnemyXMLBuilder::~EnemyXMLBuilder() {}

	map<wstring, shared_ptr<EnemyXMLCreatorBase>>& EnemyXMLBuilder::GetCreatorMap() const {
		return pImpl->m_CreatorMap;
	}

	void EnemyXMLBuilder::CreateFromXML(const wstring& ClsName, const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode) {
		auto it = pImpl->m_CreatorMap.find(ClsName);
		if (it == pImpl->m_CreatorMap.end()) {
			return;
		}
		else {
			(*it).second->Create(StagePtr, pNode);
			return;
		}
	}

	void EnemyXMLBuilder::CreateFromXML(const wstring& ClsName, const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode) {
		auto it = pImpl->m_CreatorMap.find(ClsName);
		if (it == pImpl->m_CreatorMap.end()) {
			return;
		}
		else {
			(*it).second->Create(StagePtr, pNode);
			return;
		}
	}

	void EnemyXMLBuilder::Build(const shared_ptr<Stage>& StagePtr, const wstring& XMLFileName, const wstring& GameObjectsPath) {
		try {
			//XMLリーダー
			XmlDocReader Reader(XMLFileName);
			auto Nodes = Reader.GetSelectNodes(GameObjectsPath.c_str());
			long CountNode = XmlDocReader::GetLength(Nodes);
			for (long i = 0; i < CountNode; i++) {
				auto Node = XmlDocReader::GetItem(Nodes, i);
				auto TypeStr = XmlDocReader::GetAttribute(Node, L"Type");
				CreateFromXML(TypeStr, StagePtr, Node);
			}
		}
		catch (...) {
			throw;
		}
	}

	void EnemyXMLBuilder::Build(const shared_ptr<Stage>& StagePtr, const EnemyXMLDataIN input) {
		try {
			//XMLリーダー
			XmlDocReader Reader(input.XMLFileName);
			auto ObjectNodes = Reader.GetSelectNodes(input.ObjectsPath.c_str());
			auto ParamNodes = Reader.GetSelectNodes(input.paramPath.c_str());
			auto RootPointNodes = Reader.GetSelectNodes(input.rootPointPath.c_str());

			long ObjectCount = XmlDocReader::GetLength(ObjectNodes);
			long ParamCount = XmlDocReader::GetLength(ParamNodes);
			long RootPointCount = XmlDocReader::GetLength(RootPointNodes);
			
			//パラメータのTypeを取得
			for (int i = 0; i < ParamCount; i++)
			{
				auto param = XmlDocReader::GetItem(ParamNodes,i);
				auto paramType = XmlDocReader::GetAttribute(param, L"Type");
				for (int pos = 0; pos < ObjectCount; pos++)
				{
					auto Obj = XmlDocReader::GetItem(ParamNodes, pos);
					auto ObjType = XmlDocReader::GetAttribute(Obj, L"Type");
					if (paramType == ObjType)
					{
						auto ObjCode = XmlDocReader::GetAttribute(Obj, L"Code");
						for (int root = 0; root < RootPointCount; root++)
						{
							auto Root = XmlDocReader::GetItem(RootPointNodes, root);
							auto RootCode = XmlDocReader::GetAttribute(Obj, L"Code");
							if (ObjCode == RootCode)
							{
								EnemyXMLDataOUT result(Obj, param, Root);

								CreateFromXML(ObjType, StagePtr, result);
							}
						}
					}
					else
					{
						
					}
				}
			}
			//ルート
			//出現位置

		}
		catch (...) {
			throw;
		}
	}

	//----------------------------------------
	///エネミーのエレメントデータ構造体
	//----------------------------------------
	struct ElemBase
	{
		//エネミーの状態＜巡回・追跡・索敵＞
		enum State
		{
			Wait,//停止
			Traveling,//巡回
			Tracking,//追跡
			Search//捜索
		};
		//状態メンバ変数<=ゲームマネージャーから使う
		State _state;
		//識別コード (オブジェクトクラス名)-(継承クラス名)-(個別番号)
		wstring _CODE;
		//巡回経路
		vector<Vec3> TravelingPoint;
		//捜索範囲
		float _Distance;
		//追跡対象
		shared_ptr<GameObject> _TargetObj;

		ElemBase()
			:_state(State::Traveling),TravelingPoint(NULL),_TargetObj(nullptr)
		{
			
		}

		//一番近い巡回経路を返す
		const Vec3 GetNearPoint(const Vec3 &CurrentPosition)const
		{

		}
	};
	//----------------------------------------
	//EnemyBase::Impl
	//----------------------------------------
	struct EnemyBase::Impl
	{
		ElemBase _Data;
		
		

		ElemBase GetElement();
		void SetElement(const ElemBase&Elem)
		{
			_Data = Elem;
		}
	};

	ElemBase EnemyBase::Impl::GetElement()
	{
		return _Data;
	}
	//-------------------------------------------
	//Enemyクラスの実装
	//-------------------------------------------
	EnemyBase::EnemyBase(const shared_ptr<Stage>&Stage)
		:GameObject(Stage),pImpl(new Impl())
	{

	}

	ElemBase EnemyBase::GetElement()
	{
		return pImpl->GetElement();
	}

	void EnemyBase::SetElement(const ElemBase& Elem)
	{
		pImpl->SetElement(Elem);
	}

	//-------------------------------------------
	//Enemyステートマシン実装
	//-------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(TravelingState);
    void TravelingState::Enter(const shared_ptr<EnemyBase>&obj)
	{

	}

	void TravelingState::Execute(const shared_ptr<EnemyBase>&obj)
	{

	}

	void TravelingState::Exit(const shared_ptr<EnemyBase>&Obj)
	{

	}
}