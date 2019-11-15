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
	//2.����o�H�̈ꌳ�Ǘ�
	//3.�O���t�@�C���̓Ǎ�
	//4.
	class EnemyManager:public ObjectInterface
	{
	public:
		EnemyManager();
		

		//----------------------------------------------------------------------------------
		/*!
		@brief �G�l�~�[�����p�֐�
		@paramf[in] stage�@����������^�[�Q�b�g�X�e�[�W EnemyDataPath �G�l�~�[�̏�񂪓������f�[�^�p�X
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		void GenerateEnemyObject(const shared_ptr<Stage>&TargetStage, const wstring &EnemyDataPath);

		//----------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�֐�
		@paramf[in] event �����Ă����C�x���g
		@return �Ȃ�
		*/
		//----------------------------------------------------------------------------------
		void OnEvent(const shared_ptr<Event>& event)override;

	private:
		//�R�s�[�֎~
		EnemyManager(const EnemyManager&) = delete;
		EnemyManager& operator=(const EnemyManager&) = delete;
		//���[�u�֎~
		EnemyManager(const EnemyManager&&) = delete;
		EnemyManager& operator=(const EnemyManager&&) = delete;

	};

	//�I�u�W�F�N�g�r���_�[���G�l�~�[��p�ɂ��č쐬
	
	//�G�l�~-�p�����\����
	struct EnemyXMLDataIN
	{
		wstring XMLFileName;//XML�t�@�C���p�X
		wstring ObjectsPath;//�G�l�~�[�z�u�p�X
		wstring paramPath;	//�p�����[�^�p�X
		wstring rootPointPath;//����o�H�p�X
	};

	struct EnemyXMLDataOUT
	{
		IXMLDOMNodePtr InitData;	//�������f�[�^
		IXMLDOMNodePtr Param;		//�p�����[�^
		IXMLDOMNodePtr Point;		//����n�_

		EnemyXMLDataOUT(const IXMLDOMNodePtr &InitData,const IXMLDOMNodePtr& Param,const IXMLDOMNodePtr Point)
			:InitData(InitData), Param(Param), Point(Point)
		{

		}
	};
	//--------------------------------------------------------------------------------------
	//	�G�l�~�[��p�N���G�[�^�[�N���X(�e)
	//--------------------------------------------------------------------------------------
	class EnemyXMLCreatorBase {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		explicit EnemyXMLCreatorBase() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EnemyXMLCreatorBase() {}
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Q�[���I�u�W�F�N�g���쐬����i�������z�֐��j
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	pNode	XML�m�[�h
		@return	�Q�[���I�u�W�F�N�g�̃|�C���^
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode) = 0;

		virtual shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode) = 0;
	};

	//----------------------------------------
	//�G�l�~�[XML�W�F�l���C�g
	//----------------------------------------
	template<class EXEnemy>
	class EnemyXMLCreater :public EnemyXMLCreatorBase
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		explicit EnemyXMLCreater() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EnemyXMLCreater() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�Q�[���I�u�W�F�N�g���쐬����i���z�֐��j
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	pNode	XML�m�[�h
		@return	�Q�[���I�u�W�F�N�g�̃|�C���^
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode)override {
			return StagePtr->AddGameObject<T>(pNode);
		}

		shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode)override {
			return StagePtr->AddGameObject<T>(pNode);
		}

	};

	//--------------------------------------------------------------------------------------
	//�G�l�~�[��pXML�r���_�[
	//--------------------------------------------------------------------------------------
	class EnemyXMLBuilder {
		map<wstring, shared_ptr<EnemyXMLCreatorBase>>& GetCreatorMap() const;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		EnemyXMLBuilder();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EnemyXMLBuilder();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�N���G�[�^�[��o�^����
		@tparam	T	�o�^����^�i�Q�[���I�u�W�F�N�g�̔h���j
		@param[in]	ClsName	�^�̎��ʖ��i�ʏ�͌^���𕶎���ɂ������́j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		template<typename T>
		void Register(const wstring& ClsName) {
			GetCreatorMap()[ClsName] = shared_ptr<EnemyXMLCreater<T>>(new EnemyXMLCreater<T>());
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�^�̎��ʖ����g���ăQ�[���I�u�W�F�N�g���\�z����
		@param[in]	ClsName	�^�̎��ʖ��i�ʏ�͌^���𕶎���ɂ������́j
		@param[in]	StagePtr	��������X�e�[�W
		@param[in]	pNode	XML�m�[�h
		@return	�쐬�����Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		void CreateFromXML(const wstring& ClsName, const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode);

		void CreateFromXML(const wstring& ClsName, const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	XML����Q�[���I�u�W�F�N�g���\�z����
		@param[in]	StagePtr	��������X�e�[�W
		@param[in]	XMLFileName	XML�t�@�C����
		@param[in]	GameObjectsPath	�Q�[���I�u�W�F�N�g(����)�̃m�[�h�ւ̃p�X
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void Build(const shared_ptr<Stage>& StagePtr, const wstring& XMLFileName, const wstring& GameObjectsPath);

		void Build(const shared_ptr<Stage>& StagePtr, const EnemyXMLDataIN input);

		//EnemyXMLDataOUT CheckToNodeList(const IXMLDOMNodeListPtr& NodeList, const int &sortNum);
	private:
		// pImpl�C�f�B�I��
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//----------------------------------------
	//�G�l�~�[�̊��N���X
	//----------------------------------------
	/*!
	//----------------------------------------
	@brief
	//----------------------------------------
	*/
	//�G�������g�f�[�^�\���̐錾
	struct ElemBase;

	class EnemyBase :public GameObject
	{
	public:
		EnemyBase(const shared_ptr<Stage>&stage);

		//��������
		virtual void OnCreate()override = 0;
		//�X�V����
		virtual void OnUpdate()override = 0;
		
		virtual void SetElement(const ElemBase& Elem);

	protected:
		virtual ElemBase GetElement();
		
		friend GameManager;

		struct Impl;
		unique_ptr<Impl>pImpl;
	};


	//-----------------------------------------------------
	//�X�e�[�g�}�V���x�[�X
	//-----------------------------------------------------
	class TravelingState :public ObjState<EnemyBase>
	{
		TravelingState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(TravelingState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&Obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&Obj)override;

	};
}