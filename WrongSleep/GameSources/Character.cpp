/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	FixedObject::FixedObject(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
		:GameObject(stage)
	{
		auto MeshStr = XmlDocReader::GetAttribute(pNode, L"Mesh");
		auto TexStr = XmlDocReader::GetAttribute(pNode, L"Tex");
		auto PositionStr = XmlDocReader::GetAttribute(pNode, L"Pos");
		auto ScaleStr = XmlDocReader::GetAttribute(pNode, L"Scale");
		auto RotetaStr = XmlDocReader::GetAttribute(pNode, L"Rot");

		//���b�V��
		_MeshKey = MeshStr;

		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PositionStr, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		_Pos = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Scale
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, ScaleStr, L',');
		_Scal = Vec3(
			(float)_wtof(Tokens[0].c_str()),
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str())
		);
		//Rot
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, RotetaStr, L',');
		//��]�́uXM_PIDIV2�v�̕�����ɂȂ��Ă���ꍇ������
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		_TexKey = TexStr;
	}

	void FixedObject::OnCreate()
	{
		auto DrawComp = AddComponent<PNTStaticDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(_MeshKey);
		DrawComp->SetTextureResource(_TexKey);

		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);
	}

}
//end basecross
