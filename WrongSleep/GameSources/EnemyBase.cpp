#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//�O����`
	class GameManager;
	class EnemyBase;
	//----------------------------------------
	///�G�l�~�[�Ǘ��N���X
	//----------------------------------------
	EnemyManager::EnemyManager()
	{

	}
	void EnemyManager::SetEnemyObject(const shared_ptr<EnemyBase> EnemyObj)
	{
		_EnemyObjects.push_back(EnemyObj);
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
	//	//�G�l�~�[�̏�ԁ�����E�ǐՁE���G��
	//	enum State
	//	{
	//		Wait,//��~
	//		Traveling,//����
	//		Tracking,//�ǐ�
	//		Search//�{��
	//	};
	//	//��ԃ����o�ϐ�<=�Q�[���}�l�[�W���[����g��
	//	State _state;
	//	//���ʃR�[�h (�I�u�W�F�N�g�N���X��)-(�p���N���X��)-(�ʔԍ�)
	//	//wstring _CODE;
	//	//����o�H
	//	map<int,Vec3> TravelingPoint;
	//	//�{���͈�
	//	float _Distance;
	//	//�ǐՑΏ�
	//	shared_ptr<GameObject> _TargetObj;

	//	EnemyParam()
	//		:_state(State::Traveling), _TargetObj(nullptr)
	//	{

	//	}
	//	~EnemyParam() {}
	//	//��ԋ߂�����o�H��Ԃ�
	//	//const Vec3 GetNearPoint(const Vec3 &CurrentPosition)const
	//	//{

	//	//}
	//			
	//};

	//-------------------------------------------
	//Enemy�N���X�̎���
	//-------------------------------------------
	//Static�ϐ��̎���
	weak_ptr<StageCellMap> EnemyBase::_CellMap;

	EnemyBase::EnemyBase(const shared_ptr<Stage>&Stage)
		:GameObject(Stage)
	{

	}

	EnemyBase::EnemyBase(const shared_ptr<Stage>&Stage, IXMLDOMNodePtr pNode)
		:GameObject(Stage)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"MeshKey");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"TexKey");
		auto PosStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		//���b�V��
		_MeshKey = MeshStr;
		//�e�N�X�`��
		_TexKey = TexStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PosStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
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
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rotate.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rotate.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rotate.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		//�I�u�W�F�N�g�p�����[�^
		//�p�����[�^�m�[�h
		//auto ParamNode = XmlDocReader::GetSelectSingleNode(pNode, L"ObjParam");

		
		//����|�W�V�����m�[�h
		auto MovePNode = XmlDocReader::GetSelectSingleNode(pNode, L"MovePoint");
		auto PointNodes = XmlDocReader::GetSelectSingleNode(MovePNode, L"Pos");
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
			//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
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

	//-------------------------------------------
	//Enemy�X�e�[�g�}�V������
	//-------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(TravelingState);
    void TravelingState::Enter(const shared_ptr<EnemyBase>&obj)
	{
		//�O��ʒu������ꍇ���̏ꏊ���ŏ���Point�ɐݒ�
		//���ݒn�_����ԋ߂�Point���擾
		//obj->GetBehavior<EnemyBehavior>()->SetPositon(obj->GetComponent<Transform>()->GetPosition());
		obj->GetBehavior<EnemyBehavior>()->SetNextPoint();
	}

	void TravelingState::Execute(const shared_ptr<EnemyBase>&obj)
	{
		//����o�H���擾
		if (obj->GetBehavior<EnemyBehavior>()->TravelingMove(2.0f))
		{
			//���B�����玟�̒n�_���擾
			obj->GetBehavior<EnemyBehavior>()->SetNextPoint();
		}
	}

	void TravelingState::Exit(const shared_ptr<EnemyBase>&Obj)
	{
		//��ԑJ�ڎ��̈ʒu���W��ێ�
	}

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

		//�o�H�T��
		auto MapPtr = _CellMap.lock();
		if (MapPtr)
		{
			AddComponent<PathSearch>(MapPtr);
		}
		else
		{
			throw BaseException(
				L"CellMap������܂���",
				L"Enemy.cpp",
				L"EnemyBase::OnCreate()"
			);
		}

	}

	void ToyGuards::OnUpdate()
	{
		m_SteteMachine->Update();
	}
}