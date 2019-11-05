/*!
@file ProjectBehavior.cpp
@brief �v���W�F�N��`�̍s���N���X����
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//�i�s�x�N�g���ւ̉��@�֐�
	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		float moveLength = 0;	//���������̃X�s�[�h
		auto ptrTransform = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		//�i�s�����̌������v�Z
		auto front = ptrTransform->GetWorldPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//�i�s������������̊p�x���Z�o
		float frontAngle = atan2(front.z, front.x);
		//�R���g���[���̌����v�Z
		float moveX = m_cntl.LX;
		float moveY = m_cntl.LY;

		Vec2 moveVec(moveX, moveY);
		float moveSize = moveVec.length();
		//�R���g���[���̌�������p�x���v�Z
		float cntlAngle = atan2(-moveX, moveY);
		//�g�[�^���̊p�x���Z�o
		float totalAngle = frontAngle + cntlAngle;
		//�p�x����x�N�g�����쐬
		angle = Vec3(cos(totalAngle), sin(totalAngle), 0);
		//���K������
		angle.normalize();
		//�ړ��T�C�Y��ݒ�B
		angle *= moveSize;
		//Z���͕ω������Ȃ�
		angle.z = 0;
		return angle;

	}
	//�v���C���[�̈ړ�����
	void Player::MovePlayer() {
		//float elapsedTime = App::GetApp()->GetScene<Scene>()->GetElpasedTime();
		Vec3 m_PlayerAngle = GetMoveVector();
		float elapsedTime = 1;


		////�����ړ�
		float m_addSpeed = 5;
		auto ThisT = GetComponent<Transform>();
		Vec3 m_playerPos = ThisT->GetPosition();
		float m_playerScale = ThisT->GetScale().x;
		auto velocity = m_PlayerAngle * m_PlayerSpeed * 5 * m_playerScale * m_addSpeed * elapsedTime;
		//Vec3 m_velocity; += velocity;

		m_ChargedVec += velocity;
		//�w��n�_�ւ̈���
		Vec3 velocity2 = m_ChargedVec - m_playerPos;
		float dis2 = length(velocity2);
		velocity2 = normalize(velocity2);
		//���͎w�肪�s���߂��Ȃ��悤�ɒ���
		m_playerPos += velocity2 * m_PlayerSpeed * dis2 *elapsedTime;
		ThisT->SetPosition(m_playerPos);

	}
}

//end basecross

