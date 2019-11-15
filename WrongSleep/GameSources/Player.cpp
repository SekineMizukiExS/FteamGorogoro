/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"
#include <experimental/generator>

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

		ptr->SetScale(5.0f, 5.0f, 5.0f);	//���a225�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0.5f, 2.5f, 0));
		//ptr->SetPivot(Vec3(0, 0, 0));
		TempPivot = ptr->GetPivot();

		cubeSizeHalf = 2.25 / 2.0f;

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		//ptrDraw->SetMeshResource(L"Player_MD");
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

		if (m_time <= 0.25f * XM_2PI && m_reverse == false) {
			m_time += 0.01;

		}
		else {
			m_reverse = true;
		}

		if (m_time >= 0 && m_reverse == true) {
			m_time -= 0.01;
		}
		else {
			m_reverse = false;
		}


		auto transptr = GetComponent<Transform>();
		Quat tempQ = transptr->GetQuaternion();
		Vec3 pivot = Vec3(0, 0.0f, 0.0f);
		Vec3 exam = Vec3(0, 0, 1);
		Vec3 exPos(0.5f, 0.5f, 0);

		//exPos = transptr->GetPosition();
		//transptr->RotateAround(pivot, exam, 0.1f);
		//transptr->RotateAround(pivot, exam, m_time,tempQ,exPos);
		//Tempbool = RotateAround(pivot, exam, m_time,transptr,Tempbool);

		//wstring tempQtx(L"tempQ: ");
		//tempQtx += Util::FloatToWStr(tempQ.getW()) + L"\n";
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(tempQtx);

		//Quat q = Quat(Vec3(0,0,1), m_time);

		//transptr->SetQuaternion(q);

		////transptr->(Vec3(0, 0, m_time));
		//if (m_time >= 25) {
		////	transptr->SetPivot(TempPivot);
		//}


		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		Vec3 nowPos = transptr->GetPosition();
		float maxrot = 0.5f * XM_PI;


		//==========================Unity�ڐA��========================
					//Debug.Log("hol:" + Input.GetAxis("Horizontal"));
			//��]���͓��͂��󂯕t���Ȃ�
		if (isRotate == true) {
			if (m_count < 5) {

				pivot = rotatePoint;
				exam = rotateAxis;
				transptr->RotateAround(pivot, exam, 0.1f * XM_PI, nowPos);
				m_count += 1;
			}
			else {

				m_count = 0;
				isRotate = false;

			}

			//pivot = rotatePoint;
			//exam = rotateAxis;
			//transptr->RotateAround(pivot, exam, 0.25f * XM_2PI, nowPos);
			//isRotate = false;

		}else if (moveX > 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			rotatePoint = Vec3(xHalfSize, yHalfSizeMin, 0.0f);
			rotateAxis = Vec3(0, 0, 1);
			isRotate = true;

			
			//beforePos = transptr->GetPosition();
			//beforeQ = transptr->GetQuaternion();
			
		}
		else if (moveX < 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			rotatePoint = Vec3(xHalfSizeMin, yHalfSizeMin, 0.0f);
			rotateAxis = Vec3(0, 0, -1);
			isRotate = true;
		}
		else if (moveZ > 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			rotatePoint = Vec3(0.0f, yHalfSizeMin, zHalfSize);
			rotateAxis = Vec3(-1, 0, 0);
			isRotate = true;
		}
		else if (moveZ < 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			rotatePoint = Vec3(0.0f, yHalfSizeMin, zHalfSizeMin);
			rotateAxis = Vec3(1, 0, 0);
			isRotate = true;
		}
		else {
			//nowPos = transptr->GetWorldPosition();
			//transptr->SetPosition(nowPos.x, 0.5f, nowPos.z);
			//isRotate = false;
		}
	}


	void Player::GetQuadroEdge() {
		auto ptrDraw = GetComponent<BcPNTStaticDraw>();
		auto ptrTrans = GetComponent<Transform>();
		auto mesh = ptrDraw->GetMeshResource();
		vector<VertexPosition> verteces = mesh->GetVerteces();
		xHalfSize = -99999;
		yHalfSize = -99999;
		zHalfSize = -99999;
		xHalfSizeMin = 99999;
		yHalfSizeMin = 99999;
		zHalfSizeMin = 99999;
		auto worldmat = ptrTrans->GetWorldMatrix();
		
		for each (auto verPos in verteces)
		{
			verPos.position *= worldmat;
			float maxx = verPos.position.getX();
			float maxy = verPos.position.getY();
			float maxz = verPos.position.getZ();

			float minx = verPos.position.getX();
			float miny = verPos.position.getY();
			float minz = verPos.position.getZ();
			if (maxx >= xHalfSize) {
				xHalfSize = maxx;
			}
			if (maxy >= xHalfSize) {
				yHalfSize = maxy;
			}
			if (maxz >= zHalfSize) {
				zHalfSize = maxz;
			}

			//��ʂŏ㏑�����Ă���
			if (minx <= xHalfSizeMin) {
				xHalfSizeMin = minx;
			}
			if (miny <= yHalfSizeMin) {
				yHalfSizeMin = miny;
			}
			if (minz <= zHalfSizeMin) {
				zHalfSizeMin = minz;
			}
			
		}
		//xHalfSize *= ptrTrans->GetScale().getX();
		//yHalfSize *= ptrTrans->GetScale().getY();
		//zHalfSize *= ptrTrans->GetScale().getZ();
	}
		//else if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetAxis("Horizontal") <= -0.1f)
		//{
		//	rotatePoint = transform.position + new Vector3(-cubeSizeHalf, -cubeSizeHalf, 0f);
		//	rotateAxis = new Vector3(0, 0, 1);
		//}
		//else if (Input.GetKeyDown(KeyCode.UpArrow) || Input.GetAxis("Vertical") >= 0.1f)
		//{
		//	rotatePoint = transform.position + new Vector3(0f, -cubeSizeHalf, cubeSizeHalf);
		//	rotateAxis = new Vector3(1, 0, 0);
		//}
		//else if (Input.GetKeyDown(KeyCode.DownArrow) || Input.GetAxis("Vertical") <= -0.1f)
		//{
		//	rotatePoint = transform.position + new Vector3(0f, -cubeSizeHalf, -cubeSizeHalf);
		//	rotateAxis = new Vector3(-1, 0, 0);
		//}
		// ���͂��Ȃ����̓R���[�`�����Ăяo���Ȃ��悤�ɂ���
		//if (rotatePoint == Vec3(0, 0, 0))
		//	return;
		//MoveCube();
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
			*/



//end basecross

