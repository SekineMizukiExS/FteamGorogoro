/*!
@file Futon.cpp
@brief �z�c�N���X�̎���
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