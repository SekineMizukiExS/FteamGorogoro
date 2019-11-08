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
		DrawComp->SetMeshResource(L"MatTest_MD");
		DrawComp->SetTextureResource(L"Test_TX");
		DrawComp->SetDrawActive(true);
		//auto TransComp = GetComponent<Transform>();
		//TransComp->SetPosition(0, 0, 0);

		//最初のステート設定
		m_State.reset(new StateMachine<AreaBase>(GetThis<AreaBase>()));

		m_State->ChangeState(SelectAIState::Instance());
	}

	void Futon::OnUpdate()
	{
		//_timef += App::GetApp()->GetElapsedTime();

		//ParamCB temp;
		//temp.param_f.x = _timef;

		auto DrawComp = GetComponent<AreaDraw>();
		//DrawComp->UpdateParam(temp);

		m_State->Update();
		auto TransComp = GetComponent<Transform>();
		//auto mesh = DrawComp->GetMeshResource();
		//auto vert = mesh->GetBackupVerteces<VertexPositionNormalTexture>();
		//for (int i = 0; i < vert.size(); i++)
		//{
		//	auto v = vert[i].position;
		//	v.y = PALSE * sinf((i + _cnt) / 20.0f);
		//	vert[i].position = v;
		//}
		//_cnt++;
		//DrawComp->UpdateVertices(vert);

		 MeshDeform(2.0f, 2.5f, 15.0f);
		_timef += App::GetApp()->GetElapsedTime();
	}

	void Futon::MeshDeform(float amplitude, float period, float wavelength)
	{
		auto DrawComp = GetComponent<AreaDraw>();
		auto TransComp = GetComponent<Transform>();
		auto vertices = DrawComp->GetMeshResource()->GetBackupVerteces<VertexPositionNormalTexture>();
		for (auto &v : vertices)
		{
			//波源からの位置
			float x = v.position.x + TransComp->GetPosition().x;
			float z = v.position.z + TransComp->GetPosition().z;
			float r = sqrtf((x - 0)*(x - 0) + (z - 0)*(z - 0));

			auto setv = v.position;
			setv.x = x - TransComp->GetPosition().x;
			setv.y = amplitude * sinf(2.0f*XM_PI*(_timef / period - r / wavelength));
			setv.z = z - TransComp->GetPosition().z;
			v.position = setv;
		}
		_timef += App::GetApp()->GetElapsedTime();

		DrawComp->UpdateVertices(vertices);
	}
}