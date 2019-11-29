/*!
@brief　UI・演出関係
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	//------------------------------------------
	//UIクラス
	//------------------------------------------
	//-------------------------------------------------------------------------
	///スプライト
	//-------------------------------------------------------------------------
	class Sprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_halfSize;
		//バックアップ頂点データ
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

	//生成時に縦横の長さを任意で指定できるタイプのスプライトです
	class VariableSprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec2 m_startPos;
		wstring m_textureKey;
		float m_halfSizeX;//横幅
		float m_halfSizeY;//縦幅
		float m_fillAmount;//塗りつぶし度合い（フィルアマウント）
		Col4 m_color = Col4(1.0, 1.0, 1.0, 1.0);//カラー

		bool m_porigonMode;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;

		//頂点配列（縦横５個ずつ表示）
		vector<VertexPositionColorTexture> m_vertices = {
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, m_halfSizeY, 0),m_color, Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, m_halfSizeY, 0), m_color, Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, -m_halfSizeY, 0), m_color, Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, -m_halfSizeY, 0), m_color, Vec2(1.0f, 1.0f)) },
		};

		//ビルボード
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
		//選択されているかどうか

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

		//点滅
		void Blink();
		//待機
		void Wait();
		//早く点滅
		void Flash();

		Select GetSelect() { return m_Select; }
		void SetSelect(Select s) {
			m_Select = s;
			m_TotalTime = 0.0f;
		}
		float GetTotalTime() { return m_TotalTime; }

	};

	//-------------------------------------------------------------------------
	///数字スプライト
	//-------------------------------------------------------------------------
	class NumberSprite : public GameObject {
	protected:
		bool m_trace;
		Vec2 m_startScale;
		Vec3 m_startPos;
		wstring m_textureKey;
		float m_halfSizeX;//横幅
		float m_halfSizeY;//縦幅
		int m_drawNumber;//表示する数字
		//バックアップ頂点データ
		vector<VertexPositionColor>  vertices;

		//頂点配列（縦横５個ずつ表示）
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