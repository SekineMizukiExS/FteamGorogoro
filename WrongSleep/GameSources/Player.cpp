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
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 50.0f, 320.0f, 360.0f));


		auto ptr = AddComponent<Transform>();

		ptr->SetScale(2.25f, 2.25f, 2.25f);	//���a225�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 0.125f, 0));
		//ptr->SetPivot(Vec3(0, 0, 0));
		TempPivot = ptr->GetPivot();

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

	void Player::DebugLine()
	{


	}

	//bool Player::RotateAround(const bsm::Vec3& point, const bsm::Vec3& axis, float angle,shared_ptr<Transform> tr,bool onoff) {
	//	if (onoff) {
	//		Vec3 TempPivot = tr->GetPivot();
	//		tr->SetPivot(point);
	//		Quat q = Quat(axis, angle);
	//		tr->SetQuaternion(q);
	//		//tr->SetRotation(axis);
	//		return false;
	//	}
	//	else {
	//		tr->SetPivot(TempPivot);
	//		return true;
	//	}
	//}

	void Player::OnUpdate() {
		//GetMoveVector();
		//MovePlayer();
		m_time += 0.1;
		auto transptr = GetComponent<Transform>();
		Quat tempQ = transptr->GetQuaternion();
		Vec3 pivot = Vec3(0, -2, 0);
		Vec3 exam = Vec3(1, 0, 0);
		Vec3 exPos(0, 0, 0);

		transptr->RotateAroundQ(pivot, exam, m_time,tempQ,exPos);
		//Tempbool = RotateAround(pivot, exam, m_time,transptr,Tempbool);

		wstring tempQtx(L"tempQ: ");
		tempQtx += Util::FloatToWStr(tempQ.getW()) + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(tempQtx);
		
		//Quat q = Quat(Vec3(0,0,1), m_time);

		//transptr->SetQuaternion(q);

		////transptr->(Vec3(0, 0, m_time));
		//if (m_time >= 25) {
		////	transptr->SetPivot(TempPivot);
		//}
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

