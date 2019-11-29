/*!
@brief�@UI�E���o�֌W
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	//------------------------------------------
	//UI�N���X
	//------------------------------------------
	//-------------------------------------------------------------------------
	///�X�v���C�g
	//-------------------------------------------------------------------------
	class Sprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_halfSize;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor>  vertices;
	public:
		Sprite(
			const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			bool trace,
			const Vec2& startScale,
			const Vec3& startPos,
			const float halfSize
		);
		virtual	~Sprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override {}
	};

	//�������ɏc���̒�����C�ӂŎw��ł���^�C�v�̃X�v���C�g�ł�
	class VariableSprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec2 m_startPos;
		wstring m_textureKey;
		float m_halfSizeX;//����
		float m_halfSizeY;//�c��
		float m_fillAmount;//�h��Ԃ��x�����i�t�B���A�}�E���g�j
		Col4 m_color = Col4(1.0, 1.0, 1.0, 1.0);//�J���[

		bool m_porigonMode;
		//���̃I�u�W�F�N�g�݂̂Ŏg�p����X�N�G�A���b�V��
		shared_ptr<MeshResource> m_SquareMeshResource;

		//���_�z��i�c���T���\���j
		vector<VertexPositionColorTexture> m_vertices = {
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, m_halfSizeY, 0),m_color, Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, m_halfSizeY, 0), m_color, Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, -m_halfSizeY, 0), m_color, Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, -m_halfSizeY, 0), m_color, Vec2(1.0f, 1.0f)) },
		};

		//�r���{�[�h
		Quat Billboard(const Vec3& Line) {
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f) {
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
	public:
		VariableSprite(
			const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			bool trace,
			const Vec3& startPos,
			const float halfSizeX,
			const float halfSizeY,
			const bool porigonMode
		);
		virtual	~VariableSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void fillUpdate();

		void Setfill(float n);
		float Getfill();
		void SetColor(float r, float g, float b, float a);

		void SetSize(float x, float y) {
			m_halfSizeX = x;
			m_halfSizeY = y;
		}
		float GetSizeX() {
			return m_halfSizeX;
		}
		float GetSizeY() {
			return m_halfSizeY;
		}
	};

	enum Select
	{
		On,
		Off,
		Decision
	};

	class SelectSprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_halfSize;
		float m_TotalTime;
		int m_num;
		//�I������Ă��邩�ǂ���

		Select m_Select;

		vector<VertexPositionColorTexture> vertices;
	public:
		SelectSprite(
			const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			bool trace,
			const Vec2& startScale,
			const Vec3& startPos,
			const float halfSize,
			const int num
		);
		virtual	~SelectSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�_��
		void Blink();
		//�ҋ@
		void Wait();
		//�����_��
		void Flash();

		Select GetSelect() { return m_Select; }
		void SetSelect(Select s) {
			m_Select = s;
			m_TotalTime = 0.0f;
		}
		float GetTotalTime() { return m_TotalTime; }

	};

	//-------------------------------------------------------------------------
	///�����X�v���C�g
	//-------------------------------------------------------------------------
	class NumberSprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_halfSizeX;//����
		float m_halfSizeY;//�c��
		int m_drawNumber;//�\�����鐔��
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor>  vertices;

		//���_�z��i�c���T���\���j
		vector<VertexPositionColorTexture> m_vertices = {
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, m_halfSizeY, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, m_halfSizeY, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, -m_halfSizeY, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, -m_halfSizeY, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
	public:
		NumberSprite(
			const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			bool trace,
			const Vec3& startPos,
			const float halfSizeX,
			const float halfSizeY,
			const int m_drawNumber
		);
		virtual	~NumberSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void SetNumber(int n) {
			m_drawNumber = n;
		};
	};
}