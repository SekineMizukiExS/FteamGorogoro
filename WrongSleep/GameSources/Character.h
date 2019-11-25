/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//-------------------------------------------------------------------------------------
	//ステージ作成用クラス
	//-------------------------------------------------------------------------------------
	class StageObjects :public GameObject
	{
	public:
		StageObjects(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		virtual void OnCreate() override;

	private:
		wstring _MeshKey;
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _TexKey;
	};

	//--------------------------------------------------------------------------------------
	//　タイリングする固定のボックス
	//--------------------------------------------------------------------------------------
	class TilingFixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
	public:
		//構築と破棄
		TilingFixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic
		);
		virtual ~TilingFixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};


	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring _TexKey;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~FixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
//	class CMeshBox : public GameObject;
//--------------------------------------------------------------------------------------
	class CMeshBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring _TexKey;
		wstring _MeshKey;
	public:
		//構築と破棄
		CMeshBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const wstring TexKey,
			const wstring MeshKey

		);

		virtual ~CMeshBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};
}
//end basecross
