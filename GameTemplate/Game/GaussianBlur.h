#pragma once
namespace nsHikageri
{
	class GaussianBlur
	{
	public:
		/// @brief ������
		/// @param originalTexture �K�E�V�A���u���[��������I���W�i���̃e�N�X�`��
		void Init(Texture* originalTexture);

		/// @brief �K�E�V�A���u���[��GPU��Ŏ��s�B
		/// <remarks>
		/// �{�֐��̌Ăяo���́ADirectX12�𗘗p�����`��R�}���h�������ɌĂяo���K�v������܂��B
		/// </remarks>
		/// @param rc �����_�����O�^�[�Q�b�g
		/// @param blurPower �u���[�̋����B�l���傫����Α傫�����{�P�������Ȃ�B
		void ExecuteOnGPU(RenderContext& rc, float blurPower);

		/// @brief �{�P�e�N�X�`�����擾
		Texture& GetBokeTexture()
		{
			return m_yBlurRenderTarget.GetRenderTargetTexture();
		}

	private:
		/// @brief �����_�����O�^�[�Q�b�g��������
		void InitRenderTargets();

		/// @brief �X�v���C�g�̏�����
		void InitSprites();

		/// @brief �d�݃e�[�u�����X�V����B
		void UpdateWeightsTable(float blurPower);

		enum { NUM_WEIGHTS = 8 };				//�d�݂̐��B
		float m_weights[NUM_WEIGHTS];			//�d�݃e�[�u��
		Texture* m_originalTexture = nullptr;	//�I���W�i���e�N�X�`��
		RenderTarget m_xBlurRenderTarget;		//���{�P�摜��`�悷�郌���_�����O�^�[�Q�b�g
		RenderTarget m_yBlurRenderTarget;		//�c�{�P�摜��`�悷�郌���_�����O�^�[�Q�b�g
		Sprite m_xBlurSprite;					//���{�P�摜��`�悷�邽�߂̃X�v���C�g
		Sprite m_yBlurSprite;					//�c�{�P�摜��`�悷�邽�߂̃X�v���C�g
	};

}