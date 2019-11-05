/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
//	class Player : public GameObject;
//	用途: プレイヤー
//--------------------------------------------------------------------------------------
//構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr), m_cntlNum(0)
	{}

	void Player::OnCreate() {

		auto ptr = AddComponent<Transform>();

		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 0.125f, 0));


		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		//ptrDraw->SetTextureResource(L"TRACE_TX");
		//SetAlphaActive(true);



	}

	void Player::OnUpdate() {
		GetMoveVector();
	}



}
//end basecross

