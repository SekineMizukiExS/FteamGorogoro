/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//-------------------------------------------------------------------------------------
	//�X�e�[�W�쐬�p�N���X
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
	//���I�u�W�F�N�g�N���X(�X�C�b�`�ŉ�)
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

		//�ړ��p�ϐ�
		//�o�ߎ���
		float _CurrntTime;
		//�X�^�[�g
		Vec3 _Start, _End;
		//
		bool _OnEventFlag;

	};

	//--------------------------------------------------------------------------------------
	//�X�C�b�`�N���X
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
		//�J��Ԃ��g�p�ł��邩
		bool _roop;
		//�X�C�b�`�̏��
		bool _ActiveFlag;
		//�C�x���g���M�pKEY
		wstring _LinkKey;
	};

	//--------------------------------------------------------------------------------------
	//�@�^�C�����O����Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
	public:
		//�\�z�Ɣj��
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic
		);
		virtual ~TilingFixedBox();
		//������
		virtual void OnCreate() override;
		//����
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
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		//����
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
		//�\�z�Ɣj��
		CMeshBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CMeshBox();
		//������
		virtual void OnCreate() override;
		//����
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
		//�\�z�Ɣj��
		CBoneMeshBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			//const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CBoneMeshBox();
		//������
		virtual void OnCreate() override;
		//����
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
		//�\�z�Ɣj��
		CommonBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CommonBox();
		//������
		virtual void OnCreate() override;
		//����
	};

	//-----------------------------------------------------------------
	//�C�x���g�֌W�I�u�W�F�N�g�錾
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	//�C�x���g�J�����p�����[�^�\����
	//-----------------------------------------------------------------
	//struct EventCameraParam
	//{
	//	//�J�������W
	//	vector<Vec3> _TargetEyePos;
	//	//�����_
	//	vector<Vec3> _TargetAtPos;
	//	//�C�x���g��J������߂����ǂ���
	//	bool _IsStay;
	//	EventCameraParam()
	//	{}
	//	EventCameraParam(const vector<Vec3> TEyePos, const vector<Vec3> TAtPos,bool Stay = false)
	//		:_TargetEyePos(TEyePos),_TargetAtPos(TAtPos),_IsStay(Stay)
	//	{}

	//};
	//-----------------------------------------------------------------
	//�C�x���g�J�����}���N���X
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
			_CurrntEyePos = Pos;
		}

		const Vec3 &GetAtPos()const
		{
			return _CurrntAtPos;
		}

	private:
		unique_ptr<StateMachine<EventCameraMan>> _StateMachine;

		Vec3 _CurrntEyePos;
		Vec3 _CurrntAtPos;
	};

	//-------------------------------------------------------------------
	//�C�x���g�J�����X�e�[�g�}�V��
	//-------------------------------------------------------------------
	//�C�x���g�n�_�ւނ���
	class EventMove :public ObjState<EventCameraMan>
	{
		EventMove(){ }
	public:
		DECLARE_SINGLETON_INSTANCE(EventMove)
		void Enter(const shared_ptr<EventCameraMan>&obj)override;
		void Execute(const shared_ptr<EventCameraMan>&obj)override;
		void Exit(const shared_ptr<EventCameraMan>&obj)override;
	};
	//�C�x���g��
	class EventExecute :public ObjState<EventCameraMan>
	{
		EventExecute() { }
	public:
		DECLARE_SINGLETON_INSTANCE(EventExecute)
		void Enter(const shared_ptr<EventCameraMan>&obj)override;
		void Execute(const shared_ptr<EventCameraMan>&obj)override;
		void Exit(const shared_ptr<EventCameraMan>&obj)override;
	};
}
//end basecross
