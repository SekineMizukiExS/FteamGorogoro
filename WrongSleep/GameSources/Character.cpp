/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	FixedObject::FixedObject(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode)
		:GameObject(stage)
	{
		//auto MeshStr = XmlDocReader::GetAttribute(pNode, L"Mesh");
		//auto TexStr = XmlDocReader::GetAttribute(pNode, L"Tex");
		auto PositionNode = XmlDocReader::GetSelectSingleNode(pNode, L"Pos");
		auto ScaleNode = XmlDocReader::GetSelectSingleNode(pNode, L"Scale");
		auto RotetaNode = XmlDocReader::GetSelectSingleNode(pNode, L"Rot");

		wstring PositionStr = XmlDocReader::GetText(PositionNode);
		wstring ScaleStr = XmlDocReader::GetText(ScaleNode);
		wstring RotetaStr = XmlDocReader::GetText(RotetaNode);

		//メッシュ
		//_MeshKey = MeshStr;

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Position
		Tokens.clear();
		Util::WStrToTokenVector(Tokens, PositionStr, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		//回転は「XM_PIDIV2」の文字列になっている場合がある
		_Rot.x = (Tokens[0] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[0].c_str());
		_Rot.y = (Tokens[1] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[1].c_str());
		_Rot.z = (Tokens[2] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[2].c_str());

		//_TexKey = TexStr;
	}

	void FixedObject::OnCreate()
	{
		auto DrawComp = AddComponent<AreaDraw>();
		auto TransComp = AddComponent<Transform>();

		DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		DrawComp->SetTextureResource(L"Test_TX");

		TransComp->SetPosition(_Pos);
		TransComp->SetScale(_Scal);
		TransComp->SetRotation(_Rot);
	}

}
//end basecross
