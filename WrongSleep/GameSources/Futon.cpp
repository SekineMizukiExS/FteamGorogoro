/*!
@file Futon.cpp
@brief 布団クラスの実体
*/
#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Futon::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		DrawComp->SetTextureResource(L"Test_TX");
	}
}