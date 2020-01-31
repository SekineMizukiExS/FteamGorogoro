#pragma once
#include "stdafx.h"

namespace basecross
{
	class EnemyBase;
	//------------------------------------------------------
	//ステージセルマップ
	//------------------------------------------------------
	class EnemyCellMap :public StageCellMap
	{
	public:
		EnemyCellMap(const shared_ptr<Stage>& StagePtr, const wstring&MapKey, const bsm::Vec3& MiniPos, float PieceSize, UINT PieceCountX, UINT PieceCountZ, int DefaultCost = 1)
			:StageCellMap(StagePtr,MiniPos,PieceSize,PieceCountX,PieceCountZ,DefaultCost),m_MapKey(MapKey)
		{}

		EnemyCellMap(const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode);

		//初期化
		void OnCreate()override;

		//更新
		//void OnUpdate()override;

	private:
		wstring m_MapKey;
		Vec3 m_MiniPos;
		float m_PieceSize;
		UINT m_PieceCountX;
		UINT m_PieceCountZ;
		int m_DefaultCost;
	};
	//----------------------------------------
	//エネミーの管理クラス
	//----------------------------------------
	//実装予定
	class EnemyManager:public ObjectInterface
	{
	public:
		explicit EnemyManager();
		virtual ~EnemyManager();


		void OnCreate()override {};
		

		//----------------------------------------------------------------------------------
		/*!
		@brief 作成したセルマップを追加する
		@paramf[in]
		@return なし
		*/
		//----------------------------------------------------------------------------------
		void AddCellMap(const wstring&Key, const shared_ptr<EnemyCellMap>&CellMap);
		//----------------------------------------------------------------------------------
		/*!
		@brief セルマップを取得する
		@paramf[in]
		@return なし
		*/
		//----------------------------------------------------------------------------------
		weak_ptr<EnemyCellMap> GetCellMap(const wstring&Key);
		//----------------------------------------------------------------------------------
		/*!
		@brief セルマップを取得する
		@paramf[in]
		@return なし
		*/
		//----------------------------------------------------------------------------------
		vector<shared_ptr<EnemyCellMap>> GetCellMapVec();
		//----------------------------------------------------------------------------------
		/*!
		@brief イベント関数
		@paramf[in] event 送られてきたイベント
		@return なし
		*/
		//----------------------------------------------------------------------------------
		void OnEvent(const shared_ptr<Event>& event)override;
	private:
		//エネミー
		struct Impl;
		unique_ptr<Impl> pImpl;
		////コピー禁止
		EnemyManager(const EnemyManager&) = delete;
		EnemyManager& operator=(const EnemyManager&) = delete;
		//ムーブ禁止
		EnemyManager(const EnemyManager&&) = delete;
		EnemyManager& operator=(const EnemyManager&&) = delete;

	};



	//----------------------------------------
	//エネミーの基底クラス
	//----------------------------------------
	/*!
	//----------------------------------------
	@brief
	//----------------------------------------
	*/
	struct TravelingPoint
	{
		int before;
		Vec3 Point;
		int after;
		TravelingPoint(int b1, Vec3 p1, int a1)
			:before(b1),Point(p1),after(a1)
		{

		}

		inline bool operator==(const TravelingPoint& other) const
		{
			if (this->Point == other.Point&&
				this->before == other.before&&
				this->after == other.after)return true;

			return false;
		}
		inline bool operator!=(const TravelingPoint& other)const
		{
			if (this->Point != other.Point&&
				this->before != other.before&&
				this->after != other.after)return true;

			return false;

		}

	};

	class EnemyBase :public GameObject
	{
	public:
		EnemyBase(const shared_ptr<Stage>&stage);
		EnemyBase(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		virtual ~EnemyBase(){}
		//初期処理
		virtual void OnCreate()override = 0;
		//更新処理
		virtual void OnUpdate()override = 0;
		
		virtual void OnEvent(const shared_ptr<Event>& event)override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>&Object)override;

		void OnDestroy()override;

		unique_ptr<StateMachine<EnemyBase>> &GetStateMachine()
		{
			return m_SteteMachine;
		}

		vector<TravelingPoint> GetTravelingPoint()const
		{
			return _TravelingPoint;
		}

		//
		weak_ptr<EnemyCellMap> GetCellMap()const
		{
			return GameManager::GetManager()->GetEnemyManager()->GetCellMap(m_MapKey);
		}

	protected:
		friend EnemyManager;

		//ステートマシン
		unique_ptr<StateMachine<EnemyBase>> m_SteteMachine;

		//
		wstring m_MapKey;
		//unique_ptr<EnemyParam>pImpl;
		//TODO
				//Position
		Vec3 _Position;
		//Scale
		Vec3 _Scale;
		//Rotate
		Vec3 _Rotate;
		//TexKey
		wstring _TexKey;
		//MeshKey
		wstring _MeshKey;
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
		//wstring _CODE;
		//巡回経路
		vector<TravelingPoint> _TravelingPoint;
		//捜索範囲
		float _Distance;
		//追跡対象
		shared_ptr<GameObject> _TargetObj;
		//!
	};


	//-----------------------------------------------------
	//ステートマシンベース
	//-----------------------------------------------------
	//ステートマシン記述
	class TravelingState :public ObjState<EnemyBase>
	{
		TravelingState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(TravelingState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&obj)override;

	};

	//追跡中
	class TrackingState :public ObjState<EnemyBase>
	{
		TrackingState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(TrackingState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&obj)override;

	};

	//-----------------------------------------------------
	///ここから下継承クラス
	//-----------------------------------------------------
	//-----------------------------------------------------
	//ブリキ兵士
	//-----------------------------------------------------
	class ToyGuards : public EnemyBase
	{
	public:
		ToyGuards(const shared_ptr<Stage>&StagePtr)
			:EnemyBase(StagePtr)
		{}
		ToyGuards(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
			:EnemyBase(stage, pNode)
		{};


		void OnCreate()override;

		void OnUpdate()override;

	private:
		
	};

	//----------------------------------------------------
	//収集エネミー
	//----------------------------------------------------
	class CollectEnemy: public EnemyBase
	{
	public:
		CollectEnemy(const shared_ptr<Stage>&StagePtr)
			:EnemyBase(StagePtr)
		{}
		CollectEnemy(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
			:EnemyBase(stage, pNode)
		{};


		void OnCreate()override;

		void OnUpdate()override;

	private:

	};

	//------------------------------------------------------
	//収集ステート
	//------------------------------------------------------
	class CollectState :public ObjState<EnemyBase>
	{
		CollectState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(CollectState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&obj)override;

		bool Check;
	};
}