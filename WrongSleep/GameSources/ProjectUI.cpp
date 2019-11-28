/*!
@brief UI関連
*/
#include"stdafx.h"
#include "Project.h"

namespace basecross
{
	UIBase::UIBase(const shared_ptr<Stage>&StagePtr, const float Width, const float Height, const Vec2& Position, const UINT&DrawLayer)
		:GameObject(StagePtr), _Width(Width), _Height(Height), _Position(Position), _DrawLayer(DrawLayer)
	{
		//デフォルトでfalse
		SetDrawActive(false);
		SetUpdateActive(false);
		SetDrawLayer(3);
	}
}
