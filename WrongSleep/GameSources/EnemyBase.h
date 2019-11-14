#pragma once
#include "stdafx.h"

namespace basecross
{
	//----------------------------------------
	//エネミーの基底クラス
	//----------------------------------------
	/*!
	//----------------------------------------
	@brief 
	//----------------------------------------
	*/
	//エレメントデータ構造体宣言
	struct ElemBase;

	class EnemyBase :public GameObject
	{
	public:
		EnemyBase(const shared_ptr<Stage>&stage);

		//初期処理
		virtual void OnCreate()override = 0;
		//更新処理
		virtual void OnUpdate()override = 0;
		
		virtual void SetElement(const ElemBase& Elem);

	protected:
		virtual ElemBase GetElement();
		
		friend GameManager;

		struct Impl;
		unique_ptr<Impl>pImpl;
	};


	//-----------------------------------------------------
	//ステートマシン
	//-----------------------------------------------------
	template<class Enemytemp>
	class TravelingState :public ObjState<Enemytemp>
	{

	};
}