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
		Vec2 m_SizeVec;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture>  vertices;
	public:
		Sprite(
			const shared_ptr<Stage>& stagePtr,
			const wstring& textureKey,
			bool trace,
			const Vec2& startScale,
			const Vec3& startPos,
			const Vec2& SizeVec
		);
		virtual	~Sprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override = 0;
	};

	//------------------------------------------
	//�^�C�g��UI	
	//------------------------------------------
	class TitleUI :public Sprite
	{
	public:
		TitleUI(const shared_ptr<Stage>&Stage, const wstring& textureKey,
			bool trace,
			const Vec2& startScale,
			const Vec3& startPos,
			const Vec2& halfSize
		);

		~TitleUI() {}

		void OnCreate()override;

		void OnUpdate()override;
	};

	//-----------------------------------------------------------------
	//GameMaskObject
	//-----------------------------------------------------------------
	class GameMaskSprite :public GameObject
	{
	public:
		GameMaskSprite(const shared_ptr<Stage>&StagePtr,const wstring MaskTexture,const wstring FadeTexture, bool trace);
		~GameMaskSprite();

		//������
		void OnCreate()override;
		//�X�V
		void OnUpdate()override;
		//�`��
		//void OnDraw()override;

	private:
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//---------------------------------------------------
	//�A�j���[�V�����X�v���C�g
	//---------------------------------------------------
	enum AnimationType
	{
		Flashing
	};

	class AnimationSprite : public Sprite
	{
	public:
		AnimationSprite(const shared_ptr<Stage>&Stage, const wstring& textureKey,
			bool trace,
			const Vec2& startScale,
			const Vec3& startPos,
			const Vec2& halfSize,
			const float AnimationSpeed,
			const AnimationType AnimType = AnimationType::Flashing
		);
		
		~AnimationSprite() {}

		void OnCreate()override;

		void OnUpdate()override;

	private:
		AnimationType _AType;
		float _AnimationSpeed;
		float _TotalTime;
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

		wstring m_TexKey;

		weak_ptr<GameObject> m_TargetObject;
		//���̃I�u�W�F�N�g�݂̂Ŏg�p����X�N�G�A���b�V��
		shared_ptr<MeshResource> m_SquareMeshResource;
		//�w�ԍ�
		size_t m_Number;

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
		NumberSprite(
			const shared_ptr<Stage>& stagePtr,
			const shared_ptr<GameObject>& TargetObjPtr,
			const wstring& textureKey,
			bool trace,
			size_t DrawNum
		);
		virtual	~NumberSprite() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}