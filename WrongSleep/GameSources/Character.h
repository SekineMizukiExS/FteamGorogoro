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

	//--------------------------------------------------------------------------------------
	//可動オブジェクトクラス(スイッチで可動)
	//--------------------------------------------------------------------------------------
	class MovingObject :public GameObject
	{
	public:
		MovingObject(const shared_ptr<Stage>&StagePtr)
			:GameObject(StagePtr),_MoveType(MovingType::Scale)
		{}
		MovingObject(const shared_ptr<Stage>&StagePtr, IXMLDOMNodePtr pNode);

		void OnCreate()override;

		void OnUpdate()override;

		void OnEvent(const shared_ptr<Event>&event)override;

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

	};

	//--------------------------------------------------------------------------------------
	//スイッチクラス
	//--------------------------------------------------------------------------------------
	class SwitchObject : public GameObject
	{
	public:
		SwitchObject(const shared_ptr<Stage>&stage)
			:GameObject(stage)
		{}

		SwitchObject(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		void OnCreate()override;

		void OnUpdate()override
		{
			GetComponent<Transform>()->SetPosition(40, 0.5, -6);
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
	public:
		//構築と破棄
		CommonBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CommonBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};
}
//end basecross
