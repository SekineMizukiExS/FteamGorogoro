/*!

@file ProjectBehavior.h
@brief プロジェク定義の行動クラス実体

*/

#pragma once
#include "stdafx.h"


//
#define INPUT_CODE_MOVE 0x10
#define INPUT_CODE_ROT 0x20
#define INPUT_CODE_HUMAN 0x40

#define INPUT_CODE_UP 0x01
#define INPUT_CODE_DOWN 0x02
#define INPUT_CODE_RIGHT 0x04
#define INPUT_CODE_LEFT 0x08

namespace basecross {

	struct Controller
	{

		float LX;
		float LY;
		float RX;
		float RY;

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

		void SetSetCntlLX(float set) {
			LX = set;
		}
		void SetSetCntlLY(float set) {
			LY = set;
		}
		void SetSetCntlRX(float set) {
			RX = set;
		}
		void SetSetCntlRY(float set) {
			RY = set;
		}
	};
	//-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------
	class AreaBehavior :public Behavior
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!

		!*/
		//--------------------------------------------------------------------------------------
		AreaBehavior(const shared_ptr<GameObject>&GameObjectPtr)
			:Behavior(GameObjectPtr)
		{}
		void SetInputCode(const int& CODE);

	private:
		enum class SwitchIO
		{
			Stop,
			Excute
		};

		void Move();
		void Rot();

		void CheckQuat(float CheckVal);
		//float ExeTime(float nowtime);
		//
		void InputController();
		//
		bool _moveb = false, _rotb = false;
		float _ptime = 0.0f, _rtime = 0.0f;
		float _rotval = 0.0f;

		const float _MaxQuat = XM_PIDIV4;
		SwitchIO _rotsw = SwitchIO::Excute;

		//

		//

	};
	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(int num, Controller& cntl) {


			//?L?[?{?[?h??擾
			auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (keyState.m_bPushKeyTbl['W']) {
				//?O

			//
				auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
				if (keyState.m_bPushKeyTbl['W']) {
					//

					cntl.SetCntlLY(1.0f);
					return;
				}
				else if (keyState.m_bPushKeyTbl['A']) {

					cntl.SetCntlLX(-1.0f);
					return;
				}
				else if (keyState.m_bPushKeyTbl['S']) {

					cntl.SetCntlLY(-1.0f);
					return;
				}
				else if (keyState.m_bPushKeyTbl['D']) {

					cntl.SetCntlLX(1.0f);
					return;
				}
				if (keyState.m_bLastKeyTbl[VK_SPACE]) {
					cntl.SetCntlA();
					return;
				}

				auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (cntlVec[num].bConnected) {
					//L?X?e?B?b?N ???????v????
					if (cntlVec[num].fThumbLX <= 0.5f || cntlVec[num].fThumbLX >= -0.5f ||
						cntlVec[num].fThumbLY <= 0.5f || cntlVec[num].fThumbLY >= -0.5f) {
						//?R???g???[?????????v?Z

				//
						cntl.LX = cntlVec[num].fThumbLX;
						cntl.LY = cntlVec[num].fThumbLY;
					}
					else {
						cntl.LX = 0;
						cntl.LY = 0;
					}

					if (cntlVec[num].fThumbRX <= 0.5f || cntlVec[num].fThumbRX >= -0.5f ||
						cntlVec[num].fThumbRY <= 0.5f || cntlVec[num].fThumbRY >= -0.5f) {
						cntl.RX = cntlVec[num].fThumbRX;
						cntl.RY = cntlVec[num].fThumbRY;
					}
					else {
						cntl.RX = 0;
						cntl.RY = 0;
					}


					//A?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_A) {
						cntl.A = true;
					}
					//B?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_B) {
						cntl.B = true;
					}
					//X?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_X) {
						cntl.X = true;
					}
					//Y?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_Y) {
						cntl.Y = true;
					}
					//LB?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
						cntl.LB = true;
					}
					//RB?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
						cntl.RB = true;
					}
					//Start?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_START) {
						cntl.Start = true;
					}
					//Back?{?^??
					if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_BACK) {
						cntl.Back = true;
					}
				}
			}

		}
	};

	//------------------------------------------------------------------------
	///エネミー行動クラス
	//------------------------------------------------------------------------
	struct TravelingPoint;
	class EnemyBehavior :public Behavior
	{
	public:
		EnemyBehavior(const shared_ptr<GameObject>&GameObjectPtr)
			:Behavior(GameObjectPtr), _NextKey(0), _RotActive(false),_MoveActive(false),_TestMove(true), _count(0), _RotPoint(Vec3(0)), _RotAxis(Vec3(0))
		{}
		
		//移動完了したらTRUE
		bool TravelingMove(float MoveTime);

		//プレイヤーを発見したらTRUE
		//bool SearchPlayer();
		void SetNextPoint();

		void SetTargetObject(const shared_ptr<GameObject> &obj)
		{
			_TargetObject = obj;
		}

		void SetPositon(const Vec3& Pos)
		{
			_CurrntPos = Pos;
		}
	private:
		//一番近い座標を返す
		Vec3 GetPoint(const Vec3& CurrntPosition, const vector<TravelingPoint>& Point);

		//回転移動
		bool RotateMove();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目的の場所をサーチする
		@param[in]	ActiveObject	呼び出したオブジェクト
		@param[in]	TargetPos	目的の箇所
		@return	セル上に見つかったらtrue
		*/
		//--------------------------------------------------------------------------------------
		bool Search(const Vec3& TargetPos);

		//現在位置
		Vec3 _CurrntPos;
		//状態遷移時の位置
		Vec3 _BreakPos;
		//目的地
		Vec3 _MovePoint;
		//次のPointのkey;
		int _NextKey;
		//経過時間
		float _TotalTime;
		//TargetObject(プレイヤー)
		shared_ptr<GameObject> _TargetObject;

		//移動変数
		//回転中はTrue
		bool _RotActive;
		bool _MoveActive;
		bool _TestMove;
		int _count;
		Vec3 _RotPoint;
		Vec3 _RotAxis;
		bool _XActive = false, _ZActive = false;
		int key = 1;

		//セルマップ
		vector<CellIndex> _CellPath;

		int _CellIndex;
		int _NextCellIndex;
		int _TargetCellIndex;

	};
	//！
}
//end basecross

