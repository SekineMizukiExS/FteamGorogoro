#pragma once
#include "stdafx.h"

namespace basecross
{
	class EnemyBase;
	//----------------------------------------
	//�G�l�~�[�̊Ǘ��N���X
	//----------------------------------------
	//�����\��
	//1.�G�l�~�[�̐���
	//2.����o�H�̈ꌳ�Ǘ�*
	//3.�O���t�@�C���̓Ǎ�
	//4.�������A���S���̏���
	class EnemyManager:public ObjectInterface
	{
	public:
		EnemyManager();
		virtual ~EnemyManager() {}
		//----------------------------------------------------------------------------------
		/*!
		@brief �G�l�~�[�����p�֐�
		@paramf[in] stage�@����������^�[�Q�b�g�X�e�[�W EnemyDataPath �G�l�~�[�̏�񂪓������f�[�^�p�X
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		void SetEnemyObject(const shared_ptr<EnemyBase> EnemyObj);

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
		vector<shared_ptr<EnemyBase>> _EnemyObjects;
		//�R�s�[�֎~
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

	protected:
		
		unique_ptr<StateMachine<EnemyBase>> &GetStateMachine()
		{
			return m_SteteMachine;
		}

		friend EnemyManager;

		//�X�e�[�g�}�V��
		unique_ptr<StateMachine<EnemyBase>> m_SteteMachine;

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
		map<int, Vec3> TravelingPoint;
		//�{���͈�
		float _Distance;
		//�ǐՑΏ�
		shared_ptr<GameObject> _TargetObj;
		//!
	};


	//-----------------------------------------------------
	//�X�e�[�g�}�V���x�[�X
	//-----------------------------------------------------
	//�X�e�[�g�}�V���̓G�l�~�[���ƂɋL�q
	class TravelingState :public ObjState<EnemyBase>
	{
		TravelingState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(TravelingState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&Obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&Obj)override;

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

		void OnUpdate()override
		{}

	private:
		
	};
}