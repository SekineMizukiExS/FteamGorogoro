/*!
@file ProjectDraw.cpp
@breif ����V�F�[�_�p�`��R���|�l���g����
!*/
#include"stdafx.h"
#include"Project.h"

namespace basecross
{
	void AreaDraw::OnDraw()
	{
		auto PtrGameObject = GetGameObject();
		//���b�V�����Ȃ���Ε`�悵�Ȃ�
		auto MeshRes = GetMeshResource();
		if (!MeshRes) {
			throw BaseException(
				L"���b�V�����쐬����Ă��܂���",
				L"if (!MeshRes)",
				L"WaterDraw::OnDraw()"
			);
		}

		auto Dev = App::GetApp()->GetDeviceResources();
		auto pID3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();

		//NULL�̃V�F�[�_���\�[�X�̏���
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };

		auto PtrT = PtrGameObject->GetComponent<Transform>();
		//�J�����𓾂�
		auto PtrCamera = PtrGameObject->OnGetDrawCamera();
		//�J�����̎擾
		Mat4x4 View, Proj;
		View = PtrCamera->GetViewMatrix();
		Proj = PtrCamera->GetProjMatrix();

		//�R���X�^���g�o�b�t�@�̐ݒ�
		AreaCB cb1;
		//�s��̐ݒ�(�]�u����)
		cb1.World = transpose(PtrT->GetWorldMatrix());
		cb1.View = transpose(View);
		cb1.Projection = transpose(Proj);

		////�G�~�b�V�u
		//cb1.Emissive = Col4(0, 0, 0, 1);
		////�f�t�B�[�Y�͂��ׂĒʂ�
		//cb1.Diffuse = Col4(1, 1, 1, 1);
		//���C�g�̐ݒ�
		auto PtrLight = PtrGameObject->OnGetDrawLight();
		cb1.LightDir = PtrLight.m_Directional;
		cb1.LightDir.w = 1.0f;
		//�e�N�X�`��
		auto shTex = GetTextureResource();
		if (shTex) {
			//�e�N�X�`��������
			cb1.ActiveFlg.x = 1;
		}
		else {
			//�`��R���|�[�l���g�ɂ̓e�N�X�`�����Ȃ�
			cb1.ActiveFlg.x = 0;
		}
		//�R���X�^���g�o�b�t�@�̍X�V
		pID3D11DeviceContext->UpdateSubresource(CBArea::GetPtr()->GetBuffer(), 0, nullptr, &cb1, 0, 0);
		//
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = MeshRes->GetNumStride();
		UINT offset = 0;
		//���_�o�b�t�@�̐ݒ�
		pID3D11DeviceContext->IASetVertexBuffers(0, 1, MeshRes->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pID3D11DeviceContext->IASetIndexBuffer(MeshRes->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
		//�`����@�i3�p�`�j
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//�X�e�[�^�X�̃|�C���^
		//����������
		float blendfact[4] = { 0.0f,0.0f,0.0f,0.0f };
		pID3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), blendfact, D3D11_DEFAULT_SAMPLE_MASK);
		//�f�v�X�X�e���V���͎g�p����
		pID3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);
		//�V�F�[�_�̐ݒ�
		pID3D11DeviceContext->VSSetShader(VSFuton::GetPtr()->GetShader(), nullptr, 0);
		pID3D11DeviceContext->PSSetShader(PSFuton::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pID3D11DeviceContext->IASetInputLayout(VSFuton::GetPtr()->GetInputLayout());

		//�e�N�X�`���ƃT���v���[
		if (shTex) {
			pID3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//�T���v���[��ݒ�
			//auto pSampler = RenderState->GetLinearWrap();
			//pID3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);
			RenderState->SetSamplerState(pID3D11DeviceContext, GetSamplerState(), 0);
		}
		else {
			//�V�F�[�_�[���\�[�X���N���A
			pID3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//�T���v���[���N���A
			RenderState->SetSamplerAllClear(pID3D11DeviceContext);
		}



		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBArea::GetPtr()->GetBuffer();
		pID3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		pID3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

		//
		ID3D11Buffer* pParamBuffer = CBParam::GetPtr()->GetBuffer();
		pID3D11DeviceContext->VSSetConstantBuffers(1, 1, &pParamBuffer);
		pID3D11DeviceContext->PSSetConstantBuffers(1, 1, &pParamBuffer);
		//
		//�����_�����O�X�e�[�g
		pID3D11DeviceContext->RSSetState(RenderState->GetCullFront());
		//�`��
		pID3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
		//�����_�����O�X�e�[�g
		pID3D11DeviceContext->RSSetState(RenderState->GetCullBack());
		//�`��
		pID3D11DeviceContext->DrawIndexed(MeshRes->GetNumIndicis(), 0, 0);
		//��n��
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
		//�f�o�C�X�̎擾
		auto pD3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
		auto Res = App::GetApp()->GetResource<TextureResource>(Key);
		pD3D11DeviceContext->PSSetShaderResources(StartSlot, NumViews, Res->GetShaderResourceView().GetAddressOf());
		auto pSampler = App::GetApp()->GetDeviceResources()->GetRenderState()->GetLinearClamp();

		pD3D11DeviceContext->PSSetSamplers(StartSlot, NumViews, &pSampler);
	}
}