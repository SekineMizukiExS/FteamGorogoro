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

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		ptr->SetScale(5.0f, 5.0f, 5.0f);	//���a225�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(8.5f, 7.5f, 0));
		//ptr->SetPivot(Vec3(0, 0, 0));

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

	void Player::OnUpdate() {
		//GetMoveVector();
		//MovePlayer();

		auto transptr = GetComponent<Transform>();

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
		if (m_isRotate == true) {
			if (m_count < 5) {
				transptr->RotateAround(m_rotatePoint, m_rotateAxis, 0.1f * XM_PI, nowPos);
				m_count += 1;
			}
			else {

				m_count = 0;
				m_isRotate = false;

			}

			//pivot = m_rotatePoint;
			//exam = m_rotateAxis;
			//transptr->RotateAround(pivot, exam, 0.25f * XM_2PI, nowPos);
			//m_isRotate = false;

		}else if (moveX > 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			m_rotatePoint = Vec3(m_xHalfSize, m_yHalfSizeMin, 0.0f);
			m_rotateAxis = Vec3(0, 0, 1);
			m_isRotate = true;

			
			//beforePos = transptr->GetPosition();
			//beforeQ = transptr->GetQuaternion();
			
		}
		else if (moveX < 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			m_rotatePoint = Vec3(m_xHalfSizeMin, m_yHalfSizeMin, 0.0f);
			m_rotateAxis = Vec3(0, 0, -1);
			m_isRotate = true;
		}
		else if (moveZ > 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			m_rotatePoint = Vec3(0.0f, m_yHalfSizeMin, m_zHalfSize);
			m_rotateAxis = Vec3(-1, 0, 0);
			m_isRotate = true;
		}
		else if (moveZ < 0)
		{
			GetQuadroEdge();
			nowPos = transptr->GetPosition();
			m_rotatePoint = Vec3(0.0f, m_yHalfSizeMin, m_zHalfSizeMin);
			m_rotateAxis = Vec3(1, 0, 0);
			m_isRotate = true;
		}
		else {
			//nowPos = transptr->GetWorldPosition();
			//transptr->SetPosition(nowPos.x, 0.5f, nowPos.z);
			//m_isRotate = false;
		}
	}


	void Player::GetQuadroEdge() {
		auto ptrDraw = GetComponent<BcPNTStaticDraw>();
		auto ptrTrans = GetComponent<Transform>();
		auto mesh = ptrDraw->GetMeshResource();
		vector<VertexPosition> verteces = mesh->GetVerteces();
		m_xHalfSize = -99999;
		m_yHalfSize = -99999;
		m_zHalfSize = -99999;
		m_xHalfSizeMin = 99999;
		m_yHalfSizeMin = 99999;
		m_zHalfSizeMin = 99999;
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
			if (maxx >= m_xHalfSize) {
				m_xHalfSize = maxx;
			}
			if (maxy >= m_xHalfSize) {
				m_yHalfSize = maxy;
			}
			if (maxz >= m_zHalfSize) {
				m_zHalfSize = maxz;
			}

			//��ʂŏ㏑�����Ă���
			if (minx <= m_xHalfSizeMin) {
				m_xHalfSizeMin = minx;
			}
			if (miny <= m_yHalfSizeMin) {
				m_yHalfSizeMin = miny;
			}
			if (minz <= m_zHalfSizeMin) {
				m_zHalfSizeMin = minz;
			}
			
		}
		//m_xHalfSize *= ptrTrans->GetScale().getX();
		//m_yHalfSize *= ptrTrans->GetScale().getY();
		//m_zHalfSize *= ptrTrans->GetScale().getZ();
	}


		//else if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetAxis("Horizontal") <= -0.1f)
		//{
		//	m_rotatePoint = transform.position + new Vector3(-cubeSizeHalf, -cubeSizeHalf, 0f);
		//	m_rotateAxis = new Vector3(0, 0, 1);
		//}
		//else if (Input.GetKeyDown(KeyCode.UpArrow) || Input.GetAxis("Vertical") >= 0.1f)
		//{
		//	m_rotatePoint = transform.position + new Vector3(0f, -cubeSizeHalf, cubeSizeHalf);
		//	m_rotateAxis = new Vector3(1, 0, 0);
		//}
		//else if (Input.GetKeyDown(KeyCode.DownArrow) || Input.GetAxis("Vertical") <= -0.1f)
		//{
		//	m_rotatePoint = transform.position + new Vector3(0f, -cubeSizeHalf, -cubeSizeHalf);
		//	m_rotateAxis = new Vector3(-1, 0, 0);
		//}
		// ���͂��Ȃ����̓R���[�`�����Ăяo���Ȃ��悤�ɂ���
		//if (m_rotatePoint == Vec3(0, 0, 0))
		//	return;
		//MoveCube();
}





//end basecross

