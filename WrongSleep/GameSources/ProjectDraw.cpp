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
				L"WaterDraw::OnDraw()"
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

	void AreaDraw::CreateMesh(const int&count,const int&distance)
	{

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
}