/*!
@file Futon.cpp
@brief •z’cƒNƒ‰ƒX‚ÌŽÀ‘Ì
*/
#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Futon::OnCreate()
	{
		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		
	}
}