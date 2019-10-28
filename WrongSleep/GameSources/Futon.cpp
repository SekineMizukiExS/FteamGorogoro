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
		auto DrawComp = AddComponent<AreaDraw>();
		DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		DrawComp->SetTextureResource(L"Test_TX");
	}

	void Futon::OnUpdate()
	{
		_timef += App::GetApp()->GetElapsedTime();

		ParamCB temp;
		temp.param_f.x = _timef;

		auto DrawComp = GetComponent<AreaDraw>();
		DrawComp->UpdateParam(temp);
		//vector<Vec3> vert;
		//DrawComp->GetStaticMeshLocalPositions(vert);
		//for (int i = 0; i < vert.size(); i++)
		//{
		//	auto v = vert[i];
		//	v.y = PALSE * sinf((i + _cnt) / 20.0f);
		//	vert[i] = v;
		//}
		//_cnt++;
		//DrawComp->UpdateVertices(vert);
	}
}