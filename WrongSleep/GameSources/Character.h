/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//-------------------------------------------------------------------------------------
	//ステージ作成用クラス
	//-------------------------------------------------------------------------------------
	class StageObjects :public GameObject
	{
	public:
		StageObjects(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		virtual void OnCreate() override;

	private:
		wstring _MeshKey;
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _TexKey;
	};

	class StageObjectsLoopTex : public StageObjects
	{
	public:
		StageObjectsLoopTex(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);
		virtual void OnCreate() override;
	private:
		wstring _MeshKey;
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _TexKey;
	};

	//------------------------------------------------------
	//SaveData
	//------------------------------------------------------
	class SaveDataObject :public GameObject, public GameEventInterface
	{
	private:
		wstring _MeshKey;
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _TexKey;
		wstring m_DataPath;
	public:
		SaveDataObject(const shared_ptr<Stage>&stage, const wstring& SaveDataPath, const wstring& MeshKey, const wstring& TexKey,
			const Vec3 Pos, const Vec3 Scale, const Vec3 Rotation);

		virtual void OnCreate() override;

		//ゲッター
		const wstring &GetSaveDataPath()const { return m_DataPath; }

		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};

	//ロードブロック
	class LoadBlock :public GameObject,public GameEventInterface
	{
	public:
		LoadBlock(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		virtual void OnCreate() override;

		virtual void OnUpdate()override;

		const wstring GetTargetPosStr()const { return _TargetPosStr; }

	private:
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _MeshKey;
		wstring _TexKey;

		//マップファイル名
		wstring _MapStr;

		wstring _TargetPosStr;

		AABB _SensingArea;
	};

	//--------------------------------------------------------------------------------------
	//可動オブジェクトクラス(スイッチで可動)
	//--------------------------------------------------------------------------------------
	class MovingObject :public GameObject,public GameEventInterface 
	{
	public:
		MovingObject(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr),_MoveType(MovingType::Scale)
		{}
		MovingObject(const shared_ptr<Stage>&StagePtr, IXMLDOMNodePtr pNode);

		void OnCreate()override;

		void OnUpdate()override;

		void OnEvent(const shared_ptr<Event>&event)override;

		void OnGameEvent(const shared_ptr<GameEvent>&event)override;

		bool GetEventFlag() const
		{
			return _EndFlag;
		}

	private:
		bool TestMove(const float TotalTime);

		enum MovingType
		{
			Position,
			Scale,
			Rotate
		};

		wstring _MeshKey;
		Vec3 _Position;
		Vec3 _Scale;
		Vec3 _Rotate;
		wstring _TexKey;
		wstring _LinkKey;
		MovingType _MoveType;

		//移動用変数
		//経過時間
		float _CurrntTime;
		//スタート
		Vec3 _Start, _End;
		//
		bool _OnEventFlag;
		bool _EndFlag = false;

	};

	//--------------------------------------------------------------------------------------
	//スイッチクラス
	//--------------------------------------------------------------------------------------
	class SwitchObject : public GameObject,public GameEventInterface
	{
	public:
		SwitchObject(const shared_ptr<Stage>&stage)
			:GameObject(stage),_ActiveFlag(false)
		{}

		SwitchObject(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		void OnCreate()override;

		void OnUpdate()override
		{
			//GetComponent<Transform>()->SetPosition(40, 0.5, -6);
		}

		//void OnEvent(const shared_ptr<Event>&event)override;

		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		//void OnCollisionExcute(const CollisionPair& Pair) override;


	private:

		wstring _MeshKey;
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _TexKey;
		//繰り返し使用できるか
		bool _roop;
		//スイッチの状態
		bool _ActiveFlag;
		//イベント送信用KEY
		wstring _LinkKey;
	};

	//--------------------------------------------------------------------------------------
	//　タイリングする固定のボックス
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
	public:
		//構築と破棄
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic
		);
		virtual ~TilingFixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};


	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring _TexKey;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~FixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
//	class CMeshBox : public GameObject;
//--------------------------------------------------------------------------------------
	class CMeshBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring _TexKey;
		wstring _MeshKey;
	public:
		//構築と破棄
		CMeshBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CMeshBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

//--------------------------------------------------------------------------------------
//	class CBoneMeshBox : public GameObject;
//--------------------------------------------------------------------------------------
	class CBoneMeshBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//wstring _TexKey;
		wstring _MeshKey;
	public:
		//構築と破棄
		CBoneMeshBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			//const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CBoneMeshBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
//	class CommonBox : public GameObject;
//--------------------------------------------------------------------------------------
	class CommonBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring _TexKey;
		wstring _MeshKey;
		wstring m_Tag;
	public:
		//構築と破棄
		CommonBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey

		);

		//Builder
		CommonBox(const shared_ptr<Stage>&StagePtr, IXMLDOMNodePtr Node);

		virtual ~CommonBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
	//	class LoopTextureBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class LoopTextureBox : public GameObject {
	protected:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring _TexKey;
		wstring _MeshKey;
	public:
		LoopTextureBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey
		);
		virtual	~LoopTextureBox() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override {}
	};

	//-----------------------------------------------------------------
	//オープニングカメラマンクラス
	//-----------------------------------------------------------------
	class OpeningCameraMan :public GameObject
	{
	public:
		OpeningCameraMan(const shared_ptr<Stage>&StagePtr, const wstring& FilePath);

		~OpeningCameraMan();

		//void OnCreate()override;

		//void OnUpdate() override;

	private:
		//ステートマシーン
		unique_ptr<StateMachine<OpeningCameraMan>> m_StateMachine;
		struct Impl;
		unique_ptr<Impl>pImpl;
	};

	//------------------------------------------------------
	//オープニングカメラステート
	//------------------------------------------------------
	//動く
	class OPCMoveToPoint :ObjState<OpeningCameraMan>
	{
		OPCMoveToPoint(){}
	public:
		DECLARE_SINGLETON_INSTANCE(OPCMoveToPoint)
		void Enter(const shared_ptr<OpeningCameraMan>&obj)override;
		void Execute(const shared_ptr<OpeningCameraMan>&obj)override;
		void Exit(const shared_ptr<OpeningCameraMan>&obj)override;
	};
	//
	//-----------------------------------------------------------------
	//イベント関係オブジェクト宣言
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	//イベントカメラパラメータ構造体
	//-----------------------------------------------------------------
	//struct EventCameraParam
	//{
	//	//カメラ座標
	//	vector<Vec3> _TargetEyePos;
	//	//注視点
	//	vector<Vec3> _TargetAtPos;
	//	//イベント後カメラを戻すかどうか
	//	bool _IsStay;
	//	EventCameraParam()
	//	{}
	//	EventCameraParam(const vector<Vec3> TEyePos, const vector<Vec3> TAtPos,bool Stay = false)
	//		:_TargetEyePos(TEyePos),_TargetAtPos(TAtPos),_IsStay(Stay)
	//	{}

	//};
	//-----------------------------------------------------------------
	//イベントカメラマンクラス
	//-----------------------------------------------------------------
	class EventCameraMan :public GameObject
	{
	public:
		EventCameraMan(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr)
		{}
		~EventCameraMan() {}

		void OnCreate()override;

		void OnUpdate()override;

		void OnEvent(const shared_ptr<Event>&event)override;

		unique_ptr<StateMachine<EventCameraMan>> &GetStateMachine()
		{
			return _StateMachine;
		}

		void SetAtPos(const Vec3& Pos) {
			_CurrntAtPos = Pos;
		}

		void SetTargetObject(const shared_ptr<MovingObject>& Target)
		{
			_TargetObject = Target;
		}

		void SetGameEvent(const shared_ptr<GameEvent>& event)
		{
			_GameEvent = event;
		}

		const Vec3 &GetAtPos()const
		{
			return _CurrntAtPos;
		}

		const weak_ptr<MovingObject> &GetTargetObject()const
		{
			return _TargetObject;
		}

		const shared_ptr<GameEvent> &GetGameEvent()const
		{
			return _GameEvent;
		}

	private:
		unique_ptr<StateMachine<EventCameraMan>> _StateMachine;

		weak_ptr<MovingObject> _TargetObject;

		shared_ptr<GameEvent> _GameEvent;

		Vec3 _CurrntEyePos;
		Vec3 _CurrntAtPos;
	};

	//-------------------------------------------------------------------
	//イベントカメラステートマシン
	//-------------------------------------------------------------------
	//待機状態
	class WaitState :public ObjState<EventCameraMan>
	{
		WaitState() { }
	public:
		DECLARE_SINGLETON_INSTANCE(WaitState)
		void Enter(const shared_ptr<EventCameraMan>&obj)override {}
		void Execute(const shared_ptr<EventCameraMan>&obj)override {}
		void Exit(const shared_ptr<EventCameraMan>&obj)override {}
	};

	//向かう
	class MoveToEventPoint :public ObjState<EventCameraMan>
	{
		MoveToEventPoint() { }
	public:
		DECLARE_SINGLETON_INSTANCE(MoveToEventPoint)
		void Enter(const shared_ptr<EventCameraMan>&obj)override;
		void Execute(const shared_ptr<EventCameraMan>&obj)override;
		void Exit(const shared_ptr<EventCameraMan>&obj)override;
	};

	//イベント中
	class EventExecute :public ObjState<EventCameraMan>
	{
		EventExecute() { }
	public:
		DECLARE_SINGLETON_INSTANCE(EventExecute)
		void Enter(const shared_ptr<EventCameraMan>&obj)override;
		void Execute(const shared_ptr<EventCameraMan>&obj)override;
		void Exit(const shared_ptr<EventCameraMan>&obj)override;
	};

	//戻す
	class MoveToStartPoint :public ObjState<EventCameraMan>
	{
		MoveToStartPoint() { }
	public:
		DECLARE_SINGLETON_INSTANCE(MoveToStartPoint)
		void Enter(const shared_ptr<EventCameraMan>&obj)override;
		void Execute(const shared_ptr<EventCameraMan>&obj)override;
		void Exit(const shared_ptr<EventCameraMan>&obj)override;
	};
}
//end basecross
