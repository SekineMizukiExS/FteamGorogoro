/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include <experimental/generator>

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

		//反転
		bool m_reverse = false;

		float m_PlayerSpeed = 0;
		Vec3 m_ChargedVec = Vec3(0,0,0);

		//座標
		Vec3 nowPos = Vec3(0, 0, 0);

		//ステートマシン
		unique_ptr<StateMachine<Player>> m_stateMachine;

		//======回転コルーチン用========
		//回転中
		bool isRotate = false;
		float cubeSizeHalf = 0;
		float cubeAngle = 15;
		Vec3 rotatePoint = Vec3(0, 0, 0);
		Vec3 rotateAxis = Vec3(0, 0, 0);



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

		std::experimental::generator<int>  MoveCube()
		{
			//回転中のフラグを立てる
			isRotate = true;

			auto transptr = GetComponent<Transform>();
			Quat tempQ = transptr->GetQuaternion();
			Vec3 pivot = Vec3(0, -2, 0);
			Vec3 exam = Vec3(1, 0, 0);
			Vec3 exPos(0, 0, 0);

			//回転処理
			float sumAngle = 0.0f; //angleの合計を保存
			while (sumAngle < 90.0f)
			{
				cubeAngle = 15.0f; //ここを変えると回転速度が変わる
				sumAngle += cubeAngle;

				// 90度以上回転しないように値を制限
				if (sumAngle > 180.0f)
				{
					cubeAngle -= sumAngle - 180.0f;
				}
				transptr->RotateAround(rotatePoint, rotateAxis, cubeAngle,tempQ, exPos);

				co_yield 0;
			}

			//回転中のフラグを倒す
			isRotate = false;
			rotatePoint = Vec3(0, 0, 0);
			rotateAxis = Vec3(0, 0, 0);
			//PlColEve.PlaySound(0);

			co_return;
		}

	};

}
//end basecross

