/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

//�萔��`
#define INPUT_CODE_MOVE 0x10
#define INPUT_CODE_ROT 0x20

#define INPUT_CODE_UP 0x01
#define INPUT_CODE_DOWN 0x02
#define INPUT_CODE_RIGHT 0x04
#define INPUT_CODE_LEFT 0x08

namespace basecross {
	struct Controller
	{
		//�R���g���[���[�X�e�B�b�N����
		float LX;
		float LY;
		float RX;
		float RY;
		//�{�^������
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
	//-----------------------------------------------------------------------------------
	///Area�p�̍s���N���X
	//-----------------------------------------------------------------------------------
	class AreaBehavior :public Behavior
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief�R���X�g���N�^
		@param[in] GameObject �Q�[���I�u�W�F�N�g
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

		bool _moveb = false, _rotb = false;
		float _ptime = 0.0f,_rtime = 0.0f;
		float _rotval = 0.0f;

		const float _MaxQuat = XM_PIDIV4;
		SwitchIO _rotsw = SwitchIO::Excute;

	};
	//--------------------------------------------------------------------------------------
	///	�R���g���[���̃n���h��
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(int num, Controller& cntl) {

			//�L�[�{�[�h�̎擾
			auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (keyState.m_bPushKeyTbl['W']) {
				//�O
				cntl.SetCntlLY(1.0f);
				return;
			}
			else if (keyState.m_bPushKeyTbl['A']) {
				//��
				cntl.SetCntlLX(-1.0f);
				return;
			}
			else if (keyState.m_bPushKeyTbl['S']) {
				//���
				cntl.SetCntlLY(-1.0f);
				return;
			}
			else if (keyState.m_bPushKeyTbl['D']) {
			//	//�E
				cntl.SetCntlLX(1.0f);
				return;
			}
			if (keyState.m_bLastKeyTbl[VK_SPACE]) {
				cntl.SetCntlA();
				return;
			}
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[num].bConnected) {
				//L�X�e�B�b�N �������v����
				if (cntlVec[num].fThumbLX <= 0.5f || cntlVec[num].fThumbLX >= -0.5f ||
					cntlVec[num].fThumbLY <= 0.5f || cntlVec[num].fThumbLY >= -0.5f) {
					//�R���g���[���̌����̌v�Z
					cntl.LX = cntlVec[num].fThumbLX;
					cntl.LY = cntlVec[num].fThumbLY;
				}
				else {
					cntl.LX = 0;
					cntl.LY = 0;
				}
				//R�X�e�b�N�@�������v����
				if (cntlVec[num].fThumbRX <= 0.5f || cntlVec[num].fThumbRX >= -0.5f ||
					cntlVec[num].fThumbRY <= 0.5f || cntlVec[num].fThumbRY >= -0.5f) {
					cntl.RX = cntlVec[num].fThumbRX;
					cntl.RY = cntlVec[num].fThumbRY;
				}
				else {
					cntl.RX = 0;
					cntl.RY = 0;
				}

				//A�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_A) {
					cntl.A = true;
				}
				//B�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_B) {
					cntl.B = true;
				}
				//X�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_X) {
					cntl.X = true;
				}
				//Y�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_Y) {
					cntl.Y = true;
				}
				//LB�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
					cntl.LB = true;
				}
				//RB�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
					cntl.RB = true;
				}
				//Start�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_START) {
					cntl.Start = true;
				}
				//Back�{�^��
				if (cntlVec[num].wPressedButtons & XINPUT_GAMEPAD_BACK) {
					cntl.Back = true;
				}
			}
		}

	};
}

//end basecross

