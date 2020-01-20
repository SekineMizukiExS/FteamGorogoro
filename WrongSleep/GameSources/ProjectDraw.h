/*!
@file ProjectDraw.h
@brief 自作シェーダ用描画コンポネントの実装
*/
#pragma once
#include "stdafx.h"

namespace basecross
{
	class AreaDraw :public SmBaseDraw
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief  コンストラクタ
		@param[in]  GameObjectPtr   ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit AreaDraw(const shared_ptr<GameObject>& GameObjectPtr)
			:SmBaseDraw(GameObjectPtr) {};
		//--------------------------------------------------------------------------------------
		/*!
		@brief  デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~AreaDraw() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief  OnCreate処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief  OnUpdate処理（空関数）
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief  OnDraw処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief  テクスチャをセットする処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTextures(UINT StartSlot, UINT NumTextuers, const wstring& Key);
		//--------------------------------------------------------------------------------------
		/*!
		@brief  シェーダーに渡す汎用パラメータの更新処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		void UpdateParam(ParamCB& param);
		//--------------------------------------------------------------------------------------
	private:
		float time;
		unsigned int count;

	};

	//--------------------------------------------------------------------------------------
	//スプライト描画用
	//--------------------------------------------------------------------------------------
	class SPDraw :public SpriteBaseDraw
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit SPDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Vertices	初期頂点の配列
		@param[in]	indices		初期インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		explicit SPDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SPDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void Draw(const MeshPrimData& data);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief  テクスチャをセットする処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTextures(UINT StartSlot, UINT NumTextuers, const wstring& Key);
		void SPDraw::SetBlendMapTextureResource(const shared_ptr<TextureResource>& TextureRes);
		void SPDraw::SetBlendMapTextureResource(const wstring& TextureKey);
		shared_ptr<TextureResource> SPDraw::GetBlendMapTextureResource() const;
	private:
		///テクスチャリソース
		weak_ptr<TextureResource> m_BlendMapTextureResource;

	};

	class MaskDraw :public SpriteBaseDraw
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit MaskDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Vertices	初期頂点の配列
		@param[in]	indices		初期インデックスの配列
		*/
		//--------------------------------------------------------------------------------------
		explicit MaskDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~MaskDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate処理（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Draw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief  テクスチャをセットする処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		void SetCBuffer(MaskCbuffer &mcb)
		{
			//行列の取得
			auto PtrTrans = GetGameObject()->GetComponent<Transform>();
			//行列の定義
			bsm::Mat4x4 World, Proj;
			World = PtrTrans->Get2DWorldMatrix();
			//射影行列の決定
			GetGameObject()->OnGet2DDrawProjMatrix(Proj);
			//行列の合成
			World *= Proj;
			//エミッシブ
			mcb.Emissive = GetEmissive();
			//デフィーズはすべて通す
			mcb.Diffuse = GetDiffuse();
			//行列の設定
			mcb.World = World;
		}

		void UpdateParam(MaskParamB &SetParam)
		{
			auto pD3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
			pD3D11DeviceContext->UpdateSubresource(CBParamMask::GetPtr()->GetBuffer(), 0, nullptr, &SetParam, 0, 0);
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief  テクスチャをセットする処理
		@return なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTextures(UINT StartSlot, UINT NumTextuers, const wstring& Key);
		void MaskDraw::SetFadeTextureResource(const shared_ptr<TextureResource>& TextureRes);
		void MaskDraw::SetFadeTextureResource(const wstring& TextureKey);
		shared_ptr<TextureResource> MaskDraw::GetFadeTextureResource() const;
	private:
		///テクスチャリソース
		weak_ptr<TextureResource> m_FadeTextureResource;
	};

}