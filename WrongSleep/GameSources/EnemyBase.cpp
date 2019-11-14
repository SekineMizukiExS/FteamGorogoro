#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//----------------------------------------
	///エネミーのエレメントデータ構造体
	//----------------------------------------
	struct ElemBase
	{
		//エネミーの状態＜巡回・追跡・索敵＞
		enum State
		{
			Traveling,//巡回
			Tracking,//追跡
			Search//捜索
		};
		//状態メンバ変数<=ゲームマネージャーから使う
		State _state;
		//識別コード (オブジェクトクラス名)-(継承クラス名)-(個別番号)
		wstring _CODE;
		//巡回経路
		vector<Vec3> TravelingPoint;
		//捜索範囲
		float _Distance;
		//追跡対象
		shared_ptr<GameObject> _TargetObj;

		ElemBase()
			:_state(State::Traveling),TravelingPoint(NULL),_TargetObj(nullptr)
		{
			
		}

		//一番近い巡回経路を返す
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
	//Enemyクラスの実装
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