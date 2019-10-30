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
		
	}

	//進行ベクトルへの加法関数
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		float moveLength = 0;	//動いた時のスピード
		auto ptrTransform = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		//進行方向の向きを計算
		auto front = ptrTransform->GetWorldPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//進行方向向きからの角度を算出
		float frontAngle = atan2(front.z, front.x);
		//コントローラの向き計算
		float moveX = m_cntl.LX;
		float moveY = m_cntl.LY;

		Vec2 moveVec(moveX, moveY);
		float moveSize = moveVec.length();
		//コントローラの向きから角度を計算
		float cntlAngle = atan2(-moveX, moveY);
		//トータルの角度を算出
		float totalAngle = frontAngle + cntlAngle;
		//角度からベクトルを作成
		angle = Vec3(cos(totalAngle), sin(totalAngle), 0);
		//正規化する
		angle.normalize();
		//移動サイズを設定。
		angle *= moveSize;
		//Z軸は変化させない
		angle.z = 0;
		return angle;

	}

}
//end basecross

