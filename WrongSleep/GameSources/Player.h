/*!=
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include "ObjUtil.h"
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
		//時
		float m_time = 0;
		//スピード
		float m_speed = 0.25f;
		float m_inputCooltime = 0.15f;//再入力までの待機時間
		//入力ハンドラー
		InputHandler<Player> m_inputHandler;
		wstring m_sharedName;

		//反転
		bool m_reverse = false;

		//座標
		Vec3 m_nowPos = Vec3(0, 0, 0);
		Vec3 m_beforePos = Vec3(0, 0, 0);

		//ステートマシン
		unique_ptr<StateMachine<Player>> m_stateMachine;

		//======回転コルーチン用========
		//回転中
		bool m_isRotate = false;
		float m_cubeAngle = 15;
		Vec3 m_rotatePoint = Vec3(0, 0, 0);
		Vec3 m_rotateAxis = Vec3(0, 0, 0);

		//接地面の四辺を格納して置く構造体
		Vec3HalfSizes m_V3HS = {0};
		Vec3 m_Buttom = Vec3(0,0,0);
		vector<VertexPosition> m_ButtomVertexs;

		float m_groundLine = 0;

		Vec3 m_nowSize = Vec3(1, 1, 1);

		int m_count = 0;
		int angleCount[7];
		int m_vCount = 0;
		int m_usingSize = 3;//現在使用可能なサイズ容量、２が初期値

		shared_ptr<EfkPlay> m_EfkPlay;

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
		//接触処理
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void DebugLine();
		//接地面の四辺を取得し、メンバ変数に代入する。
		void GetInFourEdge();
		void GetInFourEdge(bool bcheck);
		//回転移動
		void RotateMove();
		//伸びる
		void BoxExtending();
		//箱が伸びる方向を取得
		Vec3 GetExtendingAngle();
		//回転先を取得する関数
		Vec3 GetRotateVector();

		//重力処理
		void Gravity2();

		//プレイヤーの最初の底面を取得する関数
		


		/*
		std::experimental::generator<int>  MoveCube()
		{
			//回転中のフラグを立てる
			m_isRotate = true;

			auto transptr = GetComponent<Transform>();
			Quat tempQ = transptr->GetQuaternion();
			Vec3 pivot = Vec3(0, -2, 0);
			Vec3 exam = Vec3(1, 0, 0);
			Vec3 exPos(0, 0, 0);

			//回転処理
			float sumAngle = 0.0f; //angleの合計を保存
			while (sumAngle < 90.0f)
			{
				m_cubeAngle = 15.0f; //ここを変えると回転速度が変わる
				sumAngle += m_cubeAngle;

				// 90度以上回転しないように値を制限
				if (sumAngle > 180.0f)
				{
					m_cubeAngle -= sumAngle - 180.0f;
				}
				transptr->RotateAround(m_rotatePoint, m_rotateAxis, m_cubeAngle,tempQ, exPos);

				co_yield 0;
			}

			//回転中のフラグを倒す
			m_isRotate = false;
			m_rotatePoint = Vec3(0, 0, 0);
			m_rotateAxis = Vec3(0, 0, 0);
			//PlColEve.PlaySound(0);

			co_return;
		}
		*/
	};


	class PlayerMarker : public GameObject {

	private:
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
	public:
		/*!
		@brief	追従目標オブジェクトを得る
		@return	追従目標
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObject> GetTargetObject() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	追従目標オブジェクトを設定する
		@param[in]	Obj	追従目標オブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------

		PlayerMarker(const shared_ptr<Stage>& StagePtr);

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	class PlayerModel : public GameObject {

	private:
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
	public:
		/*!
		@brief	追従目標オブジェクトを得る
		@return	追従目標
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObject> GetTargetObject() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	追従目標オブジェクトを設定する
		@param[in]	Obj	追従目標オブジェクト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------

		PlayerModel(const shared_ptr<Stage>& StagePtr);

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}
//end basecross

