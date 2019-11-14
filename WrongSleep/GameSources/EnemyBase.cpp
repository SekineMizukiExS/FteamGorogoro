#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//----------------------------------------
	///�G�l�~�[�̃G�������g�f�[�^�\����
	//----------------------------------------
	struct ElemBase
	{
		//�G�l�~�[�̏�ԁ�����E�ǐՁE���G��
		enum State
		{
			Traveling,//����
			Tracking,//�ǐ�
			Search//�{��
		};
		//��ԃ����o�ϐ�<=�Q�[���}�l�[�W���[����g��
		State _state;
		//���ʃR�[�h (�I�u�W�F�N�g�N���X��)-(�p���N���X��)-(�ʔԍ�)
		wstring _CODE;
		//����o�H
		vector<Vec3> TravelingPoint;
		//�{���͈�
		float _Distance;
		//�ǐՑΏ�
		shared_ptr<GameObject> _TargetObj;

		ElemBase()
			:_state(State::Traveling),TravelingPoint(NULL),_TargetObj(nullptr)
		{
			
		}

		//��ԋ߂�����o�H��Ԃ�
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
	//Enemy�N���X�̎���
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
}