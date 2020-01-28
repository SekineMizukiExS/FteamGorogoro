/*!
@file ProjectDraw.cpp
@breif 自作シェーダ用描画コンポネント実体
!*/
#include"stdafx.h"
#include"Project.h"

namespace basecross
{
	void AreaDraw::OnDraw()
	{
		auto PtrGameObject = GetGameObject();
		//メッシュがなければ描画しない
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"メッシュが作成されていません",
				L"if (!MeshRes)",
				L"AreaDraw::OnDraw()"
			);
		}

		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();

		//NULLのシェーダリソースの準備
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };

		auto PtrT = PtrGameObject->GetComponent<Transform>();
		//カメラを得る
		auto PtrCamera = PtrGameObject->OnGetDrawCamera();
		//カメラの取得
		Mat4x4 View, Proj;
		View = PtrCamera->GetViewMatrix();
		Proj = PtrCamera->GetProjMatrix();

		//コンスタントバッファの設定
		AreaCB cb1;
		//行列の設定(転置する)
		cb1.World = transpose(PtrT->GetWorldMatrix());
		cb1.View = transpose(View);
		cb1.Projection = transpose(Proj);

		////エミッシブ
		//cb1.Emissive = Col4(0, 0, 0, 1);
		////デフィーズはすべて通す
		//cb1.Diffuse = Col4(1, 1, 1, 1);
		//ライトの設定
		auto PtrLight = PtrGameObject->OnGetDrawLight();
		cb1.LightDir = PtrLight.m_Directional;
		cb1.LightDir.w = 1.0f;
		//テクスチャ
		auto shTex = GetTextureResource();
		if (shTex) {
			//テクスチャがある
			cb1.ActiveFlg.x = 1;
		}
		else {
			//描画コンポーネントにはテクスチャがない
			cb1.ActiveFlg.x = 0;
		}
		//コンスタントバッファの更新
		pID3D11DeviceContext->UpdateSubresource(CBArea::GetPtr()->GetBuffer(), 0, nullptr, &cb1, 0, 0);
		//
		//ストライドとオフセット
		UINT stride = MeshRes->GetNumStride();
		UINT offset = 0;
		//頂点バッファの設定
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//インデックスバッファのセット
		pID3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
		//描画方法（3角形）
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//ステータスのポインタ
		//半透明処理
		float blendfact[4] = { 0.0f,0.0f,0.0f,0.0f };
		pID3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), blendfact, D3D11_DEFAULT_SAMPLE_MASK);
		//デプスステンシルは使用する
		pID3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);
		//シェーダの設定
		pID3D11DeviceContext->VSSetShader(VSFuton::GetPtr()->GetShader(), nullptr, 0);
		pID3D11DeviceContext->PSSetShader(PSFuton::GetPtr()->GetShader(), nullptr, 0);
		//インプットレイアウトの設定
		pID3D11DeviceContext->IASetInputLayout(VSFuton::GetPtr()->GetInputLayout());

		//テクスチャとサンプラー
		if (shTex) {
			pID3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//サンプラーを設定
			//auto pSampler = RenderState->GetLinearWrap();
			//pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
			RenderState->SetSamplerState(pID3D11DeviceContext, GetSamplerState(), 0);
		}
		else {
			//シェーダーリソースもクリア
			pID3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//サンプラーもクリア
			RenderState->SetSamplerAllClear(pID3D11DeviceContext);
		}



		//コンスタントバッファの設定
		ID3D11Buffer* pConstantBuffer = CBArea::GetPtr()->GetBuffer();
		pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

		//
		ID3D11Buffer* pParamBuffer = CBParam::GetPtr()->GetBuffer();
		pID3D11DeviceContext->VSSetConstantBuffers(1, 1, &pParamBuffer);
		pID3D11DeviceContext->PSSetConstantBuffers(1, 1, &pParamBuffer);
		//
		//レンダリングステート
		pID3D11DeviceContext->RSSetState(RenderState->GetCullFront());
		//描画
		pID3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
		//レンダリングステート
		pID3D11DeviceContext->RSSetState(RenderState->GetCullBack());
		//描画
		pID3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
		//後始末
		Dev->InitializeStates();

	}

	void AreaDraw::UpdateParam(ParamCB &SetParam)
	{
		auto pD3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
		pD3D11DeviceContext->UpdateSubresource(CBParam::GetPtr()->GetBuffer(), 0, nullptr, &SetParam, 0, 0);
	}

	void AreaDraw::SetTextures(UINT StartSlot, UINT NumViews, const wstring&Key)
	{
		//デバイスの取得
		auto pD3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
		auto Res = App::GetApp()->GetResource<TextureResource>(Key);
		pD3D11DeviceContext->PSSetShaderResources(StartSlot, NumViews, Res->GetShaderResourceView().GetAddressOf());
		auto pSampler = App::GetApp()->GetDeviceResources()->GetRenderState()->GetLinearClamp();

		pD3D11DeviceContext->PSSetSamplers(StartSlot, NumViews, &pSampler);
	}
	


	//--------------------------------------------------------------------------------------
	//スプライト描画用
	//--------------------------------------------------------------------------------------
	SPDraw::SPDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		SpriteBaseDraw(GameObjectPtr)
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}


	SPDraw::SPDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices) :
		SpriteBaseDraw(GameObjectPtr)
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
		try {
			CreateMesh(Vertices, indices);
		}
		catch (...) {
			throw;
		}
	}

	SPDraw::~SPDraw() {}

	void SPDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//作成されてなかったら作成する
			float HelfSize = 0.5f;
			//頂点配列
			vector<VertexPositionColorTexture> Vertices = {
				{ VertexPositionColorTexture(bsm::Vec3(-HelfSize, HelfSize, 0),bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(bsm::Vec3(HelfSize, HelfSize, 0), bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(bsm::Vec3(-HelfSize, -HelfSize, 0), bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(bsm::Vec3(HelfSize, -HelfSize, 0), bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(1.0f, 1.0f)) },
			};
			//インデックス配列
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//メッシュの作成（変更できる）
			CreateMesh(Vertices, indices);
		}
	}

	void SPDraw::OnDraw() {
		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::CullNone);
		}
		//メッシュリソースの取得
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//シェーダの設定
			Draw(PtrMeshResource->GetMashData());
		}
		//後始末
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

	void SPDraw::Draw(const MeshPrimData& data)
	{
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//NULLのシェーダリソースの準備
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		//サンプラーの準備
		ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
		//各オブジェクト共通処理
		//シェーダの設定
		//頂点シェーダ
		pD3D11DeviceContext->VSSetShader(VSSprite::GetPtr()->GetShader(), nullptr, 0);
		//インプットレイアウトの設定
		pD3D11DeviceContext->IASetInputLayout(VSSprite::GetPtr()->GetInputLayout());
		//ピクセルシェーダ
		pD3D11DeviceContext->PSSetShader(PSSprite::GetPtr()->GetShader(), nullptr, 0);
		//個別処理
		SpriteConstants sb;
		//コンスタントバッファの作成
		SetConstants(sb);
		//テクスチャ
		auto shTex = GetTextureResource();
		//ブレンドテクスチャ
		auto BTex = GetBlendMapTextureResource();
		//コンスタントバッファの更新
		pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);
		//コンスタントバッファの設定
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//頂点シェーダに渡す
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//ピクセルシェーダに渡す
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//ストライドとオフセット
		UINT stride = data.m_NumStride;
		UINT offset = 0;
		//描画方法のセット
		pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
		//頂点バッファのセット
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
		//インデックスバッファのセット
		pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		//各レンダリングステートの設定
		//ブレンドステート
		RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
		//デプスステンシルステート
		RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
		//テクスチャとサンプラー
		if (shTex) {
			pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//サンプラーを設定
			RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
			if (BTex)
			{
				pD3D11DeviceContext->PSSetShaderResources(1, 1, BTex->GetShaderResourceView().GetAddressOf());
				//サンプラーを設定
				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
			}
		}
		else {
			//シェーダーリソースもクリア
			pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//サンプラーもクリア
			RenderState->SetSamplerAllClear(pD3D11DeviceContext);
		}
		//ラスタライザステートと描画
		RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
		//描画
		pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
	}

	void SPDraw::SetTextures(UINT StartSlot, UINT NumViews, const wstring&Key)
	{
		//デバイスの取得
		auto pD3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
		auto Res = App::GetApp()->GetResource<TextureResource>(Key);
		pD3D11DeviceContext->PSSetShaderResources(StartSlot, NumViews, Res->GetShaderResourceView().GetAddressOf());
		auto pSampler = App::GetApp()->GetDeviceResources()->GetRenderState()->GetLinearClamp();

		pD3D11DeviceContext->PSSetSamplers(StartSlot, NumViews, &pSampler);
	}

	void SPDraw::SetBlendMapTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		m_BlendMapTextureResource = TextureRes;

	}

	void SPDraw::SetBlendMapTextureResource(const wstring& TextureKey) {
		this->SetBlendMapTextureResource(App::GetApp()->GetResource<TextureResource>(TextureKey));
	}

	shared_ptr<TextureResource> SPDraw::GetBlendMapTextureResource() const {
		//テクスチャがなければnullを返す
		auto shptr = m_BlendMapTextureResource.lock();
		if (shptr) {
			return shptr;
		}
		return nullptr;

	}


	MaskDraw::MaskDraw(const shared_ptr<GameObject>& GameObjectPtr) :
		SpriteBaseDraw(GameObjectPtr)
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
	}


	MaskDraw::MaskDraw(const shared_ptr<GameObject>& GameObjectPtr,
		vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices) :
		SpriteBaseDraw(GameObjectPtr)
	{
		//パイプラインステートをデフォルトの2D
		SetBlendState(BlendState::Opaque);
		SetDepthStencilState(DepthStencilState::None);
		SetRasterizerState(RasterizerState::CullBack);
		SetSamplerState(SamplerState::LinearClamp);
		try {
			CreateMesh(Vertices, indices);
		}
		catch (...) {
			throw;
		}
	}

	MaskDraw::~MaskDraw() {}

	void MaskDraw::OnCreate() {
		auto SpriteMesh = GetMeshResource();
		if (!SpriteMesh) {
			//作成されてなかったら作成する
			float HelfSize = 0.5f;
			//頂点配列
			vector<VertexPositionColorTexture> Vertices = {
				{ VertexPositionColorTexture(bsm::Vec3(-HelfSize, HelfSize, 0),bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(bsm::Vec3(HelfSize, HelfSize, 0), bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(1.0f, 0.0f)) },
				{ VertexPositionColorTexture(bsm::Vec3(-HelfSize, -HelfSize, 0), bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(bsm::Vec3(HelfSize, -HelfSize, 0), bsm::Col4(1.0f,1.0f,1.0f,1.0f), bsm::Vec2(1.0f, 1.0f)) },
			};
			//インデックス配列
			vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
			//メッシュの作成（変更できる）
			CreateMesh(Vertices, indices);
		}
	}

	void MaskDraw::SetFadeTextureResource(const shared_ptr<TextureResource>& TextureRes) {
		m_FadeTextureResource = TextureRes;

	}

	void MaskDraw::SetFadeTextureResource(const wstring& TextureKey) {
		this->SetFadeTextureResource(App::GetApp()->GetResource<TextureResource>(TextureKey));
	}

	shared_ptr<TextureResource> MaskDraw::GetFadeTextureResource() const {
		//テクスチャがなければnullを返す
		auto shptr = m_FadeTextureResource.lock();
		if (shptr) {
			return shptr;
		}
		return nullptr;

	}

	void MaskDraw::OnDraw() {
		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::CullNone);
		}
		//メッシュリソースの取得
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			//描画処理
			Draw();
		}
		//後始末
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();
	}

	void MaskDraw::Draw()
	{
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		auto MeshData = GetMeshResource()->GetMashData();
		//NULLのシェーダリソースの準備
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		//サンプラーの準備
		ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
		//各オブジェクト共通処理
		//シェーダの設定
		//頂点シェーダ
		pD3D11DeviceContext->VSSetShader(VSMask::GetPtr()->GetShader(), nullptr, 0);
		//インプットレイアウトの設定
		pD3D11DeviceContext->IASetInputLayout(VSMask::GetPtr()->GetInputLayout());
		//ピクセルシェーダ
		pD3D11DeviceContext->PSSetShader(PSMask::GetPtr()->GetShader(), nullptr, 0);
		//個別処理
		MaskCbuffer Mb;
		//コンスタントバッファの作成
		SetCBuffer(Mb);
		//テクスチャ
		auto shTex = GetTextureResource();
		//ブレンドテクスチャ
		auto BTex = GetFadeTextureResource();
		if (BTex)
			Mb.flags.x = 1;
		//コンスタントバッファの更新
		pD3D11DeviceContext->UpdateSubresource(CBMask::GetPtr()->GetBuffer(), 0, nullptr, &Mb, 0, 0);
		//コンスタントバッファの設定
		ID3D11Buffer* pConstantBuffer = CBMask::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//頂点シェーダに渡す
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//ピクセルシェーダに渡す
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

		ID3D11Buffer* pParamBuffer = CBParamMask::GetPtr()->GetBuffer();
		pD3D11DeviceContext->VSSetConstantBuffers(1, 1, &pParamBuffer);
		pD3D11DeviceContext->PSSetConstantBuffers(1, 1, &pParamBuffer);

		//ストライドとオフセット
		UINT stride = MeshData.m_NumStride;
		UINT offset = 0;
		//描画方法のセット
		pD3D11DeviceContext->IASetPrimitiveTopology(MeshData.m_PrimitiveTopology);
		//頂点バッファのセット
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, MeshData.m_VertexBuffer.GetAddressOf(), &stride, &offset);
		//インデックスバッファのセット
		pD3D11DeviceContext->IASetIndexBuffer(MeshData.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		//各レンダリングステートの設定
		//ブレンドステート
		RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
		//デプスステンシルステート
		RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
		//テクスチャとサンプラー
		if (shTex) {
			pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//サンプラーを設定
			RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
			if (BTex)
			{
				pD3D11DeviceContext->PSSetShaderResources(1, 1, BTex->GetShaderResourceView().GetAddressOf());
				//サンプラーを設定
				RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 1);
			}
		}
		else {
			//シェーダーリソースもクリア
			pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//サンプラーもクリア
			RenderState->SetSamplerAllClear(pD3D11DeviceContext);
		}
		//ラスタライザステートと描画
		RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
		//描画
		pD3D11DeviceContext->DrawIndexed(MeshData.m_NumIndicis, 0, 0);

	}
}