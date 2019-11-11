/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
	private:
		//--------------------------------------//
//----コントローラ、システム側の変数----//
//--------------------------------------//

		// コントローラから方向ベクトルを得る
		Vec2 GetInputState() const;
		Vec3 GetMoveVector() const;
		void MovePlayer();
		//文字列の表示
		void DrawStrings();


		//コントローラの番号
		const int m_cntlNum;
		//操作系
		Controller m_cntl;
		bool Tempbool = false;
		Vec3 TempPivot;
		//時
		float m_time = 0;
		//スピード
		float m_Speed = 1;
		//入力ハンドラー
		InputHandler<Player> m_inputHandler;
		wstring m_sharedName;

		float m_PlayerSpeed = 0;
		Vec3 m_ChargedVec = Vec3(0,0,0);

		//ステートマシン
		unique_ptr<StateMachine<Player>> m_stateMachine;



	public:
		//構築と破棄
//--------------------------------------------------------------------------------------
/*!
@brief	コンストラクタ
@param[in]	StagePtr	ステージ
*/
//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		void DebugLine();

		/*!
@brief	特定座標を中心に回転する
@return	なし
*/
		//--------------------------------------------------------------------------------------
		bool RotateAround(const bsm::Vec3& point, const bsm::Vec3& axis, float angle, shared_ptr<Transform> tr,bool onoff);
		//--------------------------------------------------------------------------------------
	};

}
//end basecross

