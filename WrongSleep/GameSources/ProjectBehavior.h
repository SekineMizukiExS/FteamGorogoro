/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	struct Controller
	{
		//コントローラースティック入力
		float LX;
		float LY;
		float RX;
		float RY;
		//ボタン入力
		bool A;
		bool B;
		bool X;
		bool Y;
		bool LB;
		bool RB;

		bool Start;
		bool Back;

		Controller() :
			LX(0.0f),
			LY(0.0f),
			RX(0.0f),
			RY(0.0f),
			A(false),
			B(false),
			X(false),
			Y(false),
			LB(false),
			RB(false),
			Start(false),
			Back(false)
		{}
	};

	//--------------------------------------------------------------------------------------
	///	コントローラのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(int num, Controller& cntl) {

			//キーボードの取得
			auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (keyState.m_bPushKeyTbl['W']) {
				//前
				cntl.SetCntlLY(1.0f);
				return;
			}
			else if (keyState.m_bPushKeyTbl['A']) {
				//左
				cntl.SetCntlLX(-1.0f);
				return;
			}
			else if (keyState.m_bPushKeyTbl['S']) {
				//後ろ
				cntl.SetCntlLY(-1.0f);
				return;
			}
			else if (keyState.m_bPushKeyTbl['D']) {
			//	//右
				cntl.SetCntlLX(1.0f);
				return;
			}
			if (keyState.m_bLastKeyTbl[VK_SPACE]) {
				cntl.SetCntlA();
				return;
			}
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[num].bConnected) {
				//Lスティック 条件式要調整
				if (cntlVec[num].fThumbLX <= 0.5f || cntlVec[num].fThumbLX >= -0.5f ||
					cntlVec[num].fThumbLY <= 0.5f || cntlVec[num].fThumbLY >= -0.5f) {
					//コントローラの向きの計算
					cntl.LX = cntlVec[num].fThumbLX;
					cntl.LY = cntlVec[num].fThumbLY;
				}
				else {
					cntl.LX = 0;
					cntl.LY = 0;
				}
				//Rステック　条件式要調整
				if (cntlVec[num].fThumbRX <= 0.5f || cntlVec[num].fThumbRX >= -0.5f ||
					cntlVec[num].fThumbRY <= 0.5f || cntlVec[num].fThumbRY >= -0.5f) {
					cntl.RX = cntlVec[num].fThumbRX;
					cntl.RY = cntlVec[num].fThumbRY;
				}
				else {
					cntl.RX = 0;
					cntl.RY = 0;
				}

				//Aボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_A) {
					cntl.A = true;
				}
				//Bボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_B) {
					cntl.B = true;
				}
				//Xボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_X) {
					cntl.X = true;
				}
				//Yボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_Y) {
					cntl.Y = true;
				}
				//LBボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
					cntl.LB = true;
				}
				//RBボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
					cntl.RB = true;
				}
				//Startボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_START) {
					cntl.Start = true;
				}
				//Backボタン
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_BACK) {
					cntl.Back = true;
				}
			}
		}

	};
}

//end basecross

