#pragma once
#include "stdafx.h"

namespace basecross
{
	class EnemyBase;
	//------------------------------------------------------
	//�X�e�[�W�Z���}�b�v
	//------------------------------------------------------
	class EnemyCellMap :public StageCellMap
	{
	public:
		EnemyCellMap(const shared_ptr<Stage>& StagePtr, const wstring&MapKey, const bsm::Vec3& MiniPos, float PieceSize, UINT PieceCountX, UINT PieceCountZ, int DefaultCost = 1)
			:StageCellMap(StagePtr,MiniPos,PieceSize,PieceCountX,PieceCountZ,DefaultCost),m_MapKey(MapKey)
		{}

		EnemyCellMap(const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode);

		//������
		void OnCreate()override;

		//�X�V
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
	//�G�l�~�[�̊Ǘ��N���X
	//----------------------------------------
	//�����\��
	class EnemyManager:public ObjectInterface
	{
	public:
		explicit EnemyManager();
		virtual ~EnemyManager();


		void OnCreate()override {};
		

		//----------------------------------------------------------------------------------
		/*!
		@brief �쐬�����Z���}�b�v��ǉ�����
		@paramf[in]
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		void AddCellMap(const wstring&Key, const shared_ptr<EnemyCellMap>&CellMap);
		//----------------------------------------------------------------------------------
		/*!
		@brief �Z���}�b�v���擾����
		@paramf[in]
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		weak_ptr<EnemyCellMap> GetCellMap(const wstring&Key);
		//----------------------------------------------------------------------------------
		/*!
		@brief �Z���}�b�v���擾����
		@paramf[in]
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		vector<shared_ptr<EnemyCellMap>> GetCellMapVec();
		//----------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�֐�
		@paramf[in] event �����Ă����C�x���g
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		void OnEvent(const shared_ptr<Event>& event)override;
	private:
		//�G�l�~�[
		struct Impl;
		unique_ptr<Impl> pImpl;
		////�R�s�[�֎~
		EnemyManager(const EnemyManager&) = delete;
		EnemyManager& operator=(const EnemyManager&) = delete;
		//���[�u�֎~
		EnemyManager(const EnemyManager&&) = delete;
		EnemyManager& operator=(const EnemyManager&&) = delete;

	};



	//----------------------------------------
	//�G�l�~�[�̊��N���X
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
		//��������
		virtual void OnCreate()override = 0;
		//�X�V����
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

		//�X�e�[�g�}�V��
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
		//�G�l�~�[�̏�ԁ�����E�ǐՁE���G��
		enum State
		{
			Wait,//��~
			Traveling,//����
			Tracking,//�ǐ�
			Search//�{��
		};
		
		//��ԃ����o�ϐ�<=�Q�[���}�l�[�W���[����g��
		State _state;
		//���ʃR�[�h (�I�u�W�F�N�g�N���X��)-(�p���N���X��)-(�ʔԍ�)
		//wstring _CODE;
		//����o�H
		vector<TravelingPoint> _TravelingPoint;
		//�{���͈�
		float _Distance;
		//�ǐՑΏ�
		shared_ptr<GameObject> _TargetObj;
		//!
	};


	//-----------------------------------------------------
	//�X�e�[�g�}�V���x�[�X
	//-----------------------------------------------------
	//�X�e�[�g�}�V���L�q
	class TravelingState :public ObjState<EnemyBase>
	{
		TravelingState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(TravelingState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&obj)override;

	};

	//�ǐՒ�
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
	///�������牺�p���N���X
	//-----------------------------------------------------
	//-----------------------------------------------------
	//�u���L���m
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
	//���W�G�l�~�[
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
	//���W�X�e�[�g
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