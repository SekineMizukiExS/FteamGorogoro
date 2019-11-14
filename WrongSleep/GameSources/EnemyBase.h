#pragma once
#include "stdafx.h"

namespace basecross
{
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
	//�X�e�[�g�}�V��
	//-----------------------------------------------------
	template<class Enemytemp>
	class TravelingState :public ObjState<Enemytemp>
	{

	};
}