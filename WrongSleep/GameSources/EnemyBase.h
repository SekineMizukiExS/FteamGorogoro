#pragma once
#include "stdafx.h"

namespace basecross
{
	class EnemyBase;
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
		@brief �G�l�~�[
		@paramf[in] stage�@����������^�[�Q�b�g�X�e�[�W
		@paramf[in] Builder �I�u�W�F�N�g�r���_�[
		@paramf[in]	XMLFilePath	�Q�Ƃ���XML�t�@�C���̃p�X
		@paramf[in] EnemyObjPath�@Object�f�[�^�܂ł̃p�X
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		void SetEnemyObject(const shared_ptr<GameObject>&ObjectPtr);

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

		void OnDestroy()override;

		unique_ptr<StateMachine<EnemyBase>> &GetStateMachine()
		{
			return m_SteteMachine;
		}

		vector<TravelingPoint> GetTravelingPoint()const
		{
			return _TravelingPoint;
		}

		//static �Q�b�^�[
		const static weak_ptr<StageCellMap> GetCellMap() { return _CellMap; }

		//static �Z�b�^�[
		const static void SetCellMap(const shared_ptr<StageCellMap> &CellMap)
		{
			_CellMap = CellMap;
		}

	protected:
		friend EnemyManager;

		//�X�e�[�g�}�V��
		unique_ptr<StateMachine<EnemyBase>> m_SteteMachine;

		//�X�e�[�W�Z���}�b�v
		static weak_ptr<StageCellMap> _CellMap;

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
}