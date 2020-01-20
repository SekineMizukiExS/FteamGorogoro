/*!
@file ProjectDraw.h
@brief ����V�F�[�_�p�`��R���|�l���g�̎���
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
		@brief  �R���X�g���N�^
		@param[in]  GameObjectPtr   �Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit AreaDraw(const shared_ptr<GameObject>& GameObjectPtr)
			:SmBaseDraw(GameObjectPtr) {};
		//--------------------------------------------------------------------------------------
		/*!
		@brief  �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~AreaDraw() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief  OnCreate����
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief  OnUpdate�����i��֐��j
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief  OnDraw����
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief  �e�N�X�`�����Z�b�g���鏈��
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTextures(UINT StartSlot, UINT NumTextuers, const wstring& Key);
		//--------------------------------------------------------------------------------------
		/*!
		@brief  �V�F�[�_�[�ɓn���ėp�p�����[�^�̍X�V����
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateParam(ParamCB& param);
		//--------------------------------------------------------------------------------------
	private:
		float time;
		unsigned int count;

	};

	//--------------------------------------------------------------------------------------
	//�X�v���C�g�`��p
	//--------------------------------------------------------------------------------------
	class SPDraw :public SpriteBaseDraw
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit SPDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		@param[in]	Vertices	�������_�̔z��
		@param[in]	indices		�����C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		explicit SPDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SPDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void Draw(const MeshPrimData& data);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief  �e�N�X�`�����Z�b�g���鏈��
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTextures(UINT StartSlot, UINT NumTextuers, const wstring& Key);
		void SPDraw::SetBlendMapTextureResource(const shared_ptr<TextureResource>& TextureRes);
		void SPDraw::SetBlendMapTextureResource(const wstring& TextureKey);
		shared_ptr<TextureResource> SPDraw::GetBlendMapTextureResource() const;
	private:
		///�e�N�X�`�����\�[�X
		weak_ptr<TextureResource> m_BlendMapTextureResource;

	};

	class MaskDraw :public SpriteBaseDraw
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		*/
		//--------------------------------------------------------------------------------------
		explicit MaskDraw(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	GameObjectPtr	�Q�[���I�u�W�F�N�g
		@param[in]	Vertices	�������_�̔z��
		@param[in]	indices		�����C���f�b�N�X�̔z��
		*/
		//--------------------------------------------------------------------------------------
		explicit MaskDraw(const shared_ptr<GameObject>& GameObjectPtr,
			vector<VertexPositionColorTexture>& Vertices, vector<uint16_t>& indices);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~MaskDraw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnCreate����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnUpdate�����i��֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	OnDraw����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void Draw();
		//--------------------------------------------------------------------------------------
		/*!
		@brief  �e�N�X�`�����Z�b�g���鏈��
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetCBuffer(MaskCbuffer &mcb)
		{
			//�s��̎擾
			auto PtrTrans = GetGameObject()->GetComponent<Transform>();
			//�s��̒�`
			bsm::Mat4x4 World, Proj;
			World = PtrTrans->Get2DWorldMatrix();
			//�ˉe�s��̌���
			GetGameObject()->OnGet2DDrawProjMatrix(Proj);
			//�s��̍���
			World *= Proj;
			//�G�~�b�V�u
			mcb.Emissive = GetEmissive();
			//�f�t�B�[�Y�͂��ׂĒʂ�
			mcb.Diffuse = GetDiffuse();
			//�s��̐ݒ�
			mcb.World = World;
		}

		void UpdateParam(MaskParamB &SetParam)
		{
			auto pD3D11DeviceContext = App::GetApp()->GetDeviceResources()->GetD3DDeviceContext();
			pD3D11DeviceContext->UpdateSubresource(CBParamMask::GetPtr()->GetBuffer(), 0, nullptr, &SetParam, 0, 0);
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief  �e�N�X�`�����Z�b�g���鏈��
		@return �Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTextures(UINT StartSlot, UINT NumTextuers, const wstring& Key);
		void MaskDraw::SetFadeTextureResource(const shared_ptr<TextureResource>& TextureRes);
		void MaskDraw::SetFadeTextureResource(const wstring& TextureKey);
		shared_ptr<TextureResource> MaskDraw::GetFadeTextureResource() const;
	private:
		///�e�N�X�`�����\�[�X
		weak_ptr<TextureResource> m_FadeTextureResource;
	};

}