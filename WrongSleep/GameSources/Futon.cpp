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
		auto DrawComp = AddComponent<AreaDraw>();
		DrawComp->SetMeshResource(L"MatTest_MD");
		DrawComp->SetTextureResource(L"Test_TX");

		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(0, 0, 0);

		//�ŏ��̃X�e�[�g�ݒ�
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

		auto mesh = DrawComp->GetMeshResource();
		auto vert = mesh->GetBackupVerteces<VertexPositionNormalTexture>();
		for (int i = 0; i < vert.size(); i++)
		{
			auto v = vert[i].position;
			v.y = PALSE * sinf((i + _cnt) / 20.0f);
			vert[i].position = v;
		}
		_cnt++;
		DrawComp->UpdateVertices(vert);
	}
}