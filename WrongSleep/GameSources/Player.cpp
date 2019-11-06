/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
//	class Player : public GameObject;
//	�p�r: �v���C���[
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr), m_cntlNum(0)
	{}

	void Player::OnCreate() {

		auto ptr = AddComponent<Transform>();

		ptr->SetScale(2.25f, 2.25f, 2.25f);	//���a225�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 0.125f, 0));
		

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		//�`�悷��e�N�X�`����ݒ�
		//ptrDraw->SetTextureResource(L"TRACE_TX");
		//SetAlphaActive(true);



	}

	void Player::OnUpdate() {
		//GetMoveVector();
		MovePlayer();
	}



	/*
			Vec3 rotatePoint = Vec3{ 0 };  //��]�̒��S
		Vec3 rotateAxis = Vec3{ 0 };   //��]��
		float cubeAngle = 0.0f;                //��]�p�x

			
		float cubeSizeHalf;                  //�L���[�u�̑傫���̔���
		bool isRotate = false;               //��]���ɗ��t���O�B��]���͓��͂��󂯕t���Ȃ�

		void Start()
		{
			cubeSizeHalf = transform.localScale.x / 2f;
			PlColEve = GetComponent<PlayerColiderEvents>();
		}

		void Update()
		{
			//Debug.Log("hol:" + Input.GetAxis("Horizontal"));
			//��]���͓��͂��󂯕t���Ȃ�
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
			// ���͂��Ȃ����̓R���[�`�����Ăяo���Ȃ��悤�ɂ���
			if (rotatePoint == Vector3.zero)
				return;
			StartCoroutine(MoveCube());
		}

		IEnumerator MoveCube()
		{
			//��]���̃t���O�𗧂Ă�
			isRotate = true;

			//��]����
			float sumAngle = 0f; //angle�̍��v��ۑ�
			while (sumAngle < 90f)
			{
				cubeAngle = 15f; //������ς���Ɖ�]���x���ς��
				sumAngle += cubeAngle;

				// 90�x�ȏ��]���Ȃ��悤�ɒl�𐧌�
				if (sumAngle > 180f)
				{
					cubeAngle -= sumAngle - 180f;
				}
				transform.RotateAround(rotatePoint, rotateAxis, cubeAngle);

				yield return null;
			}

			//��]���̃t���O��|��
			isRotate = false;
			rotatePoint = Vector3.zero;
			rotateAxis = Vector3.zero;
			PlColEve.PlaySound(0);

			yield break;
		}
	*/
}
//end basecross

