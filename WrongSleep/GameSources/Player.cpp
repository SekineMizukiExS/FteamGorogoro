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

		ptr->SetScale(2.25f, 2.25f, 2.25f);	//直径225センチの球体
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
		//GetMoveVector();
		MovePlayer();
	}



	/*
			Vec3 rotatePoint = Vec3{ 0 };  //回転の中心
		Vec3 rotateAxis = Vec3{ 0 };   //回転軸
		float cubeAngle = 0.0f;                //回転角度

			
		float cubeSizeHalf;                  //キューブの大きさの半分
		bool isRotate = false;               //回転中に立つフラグ。回転中は入力を受け付けない

		void Start()
		{
			cubeSizeHalf = transform.localScale.x / 2f;
			PlColEve = GetComponent<PlayerColiderEvents>();
		}

		void Update()
		{
			//Debug.Log("hol:" + Input.GetAxis("Horizontal"));
			//回転中は入力を受け付けない
			if (isRotate)
				return;

			if (Input.GetKeyDown(KeyCode.RightArrow) || Input.GetAxis("Horizontal") >= 0.1f)
			{
				rotatePoint = transform.position + new Vector3(cubeSizeHalf, -cubeSizeHalf, 0f);
				rotateAxis = new Vector3(0, 0, -1);
			}
			else if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetAxis("Horizontal") <= -0.1f)
			{
				rotatePoint = transform.position + new Vector3(-cubeSizeHalf, -cubeSizeHalf, 0f);
				rotateAxis = new Vector3(0, 0, 1);
			}
			else if (Input.GetKeyDown(KeyCode.UpArrow) || Input.GetAxis("Vertical") >= 0.1f)
			{
				rotatePoint = transform.position + new Vector3(0f, -cubeSizeHalf, cubeSizeHalf);
				rotateAxis = new Vector3(1, 0, 0);
			}
			else if (Input.GetKeyDown(KeyCode.DownArrow) || Input.GetAxis("Vertical") <= -0.1f)
			{
				rotatePoint = transform.position + new Vector3(0f, -cubeSizeHalf, -cubeSizeHalf);
				rotateAxis = new Vector3(-1, 0, 0);
			}
			// 入力がない時はコルーチンを呼び出さないようにする
			if (rotatePoint == Vector3.zero)
				return;
			StartCoroutine(MoveCube());
		}

		IEnumerator MoveCube()
		{
			//回転中のフラグを立てる
			isRotate = true;

			//回転処理
			float sumAngle = 0f; //angleの合計を保存
			while (sumAngle < 90f)
			{
				cubeAngle = 15f; //ここを変えると回転速度が変わる
				sumAngle += cubeAngle;

				// 90度以上回転しないように値を制限
				if (sumAngle > 180f)
				{
					cubeAngle -= sumAngle - 180f;
				}
				transform.RotateAround(rotatePoint, rotateAxis, cubeAngle);

				yield return null;
			}

			//回転中のフラグを倒す
			isRotate = false;
			rotatePoint = Vector3.zero;
			rotateAxis = Vector3.zero;
			PlColEve.PlaySound(0);

			yield break;
		}
	*/
}
//end basecross

