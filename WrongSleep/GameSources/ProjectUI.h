/*!
@brief　UI・演出関係
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	//------------------------------------------
	//UI基底クラス
	//------------------------------------------
	class UIBase :public GameObject
	{
	public:
		UIBase(const shared_ptr<Stage>&StagePtr, const float Width, const float Height, const Vec2& Position, const UINT&DrawLayer);
		virtual ~UIBase() {};

		virtual void OnEvent(const shared_ptr<Event>&event)override;

		virtual void OnCreate()override = 0;
		virtual void OnUpdate()override = 0;

	protected:
		void CreateSprite(const float Width, const float Height);

		void SetPosition(const Vec2& Position, const UINT &DrawLayer);
	private:
		float _Width;
		float _Height;
		Vec2 _Position;
		UINT _DrawLayer;
	};
}