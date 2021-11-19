#pragma once
#include "GaussianBlur.h"
namespace nsHikageri
{
	class PostEffectManager
	{
	private:
		PostEffectManager() = default;
		~PostEffectManager() = default;

		static PostEffectManager* m_instance;

	public:

		static void CreateInstance()
		{
			if (!m_instance)
			{
				m_instance = new PostEffectManager;

			}
		}

		static void DeleteInstance()
		{
			delete m_instance;
			m_instance = nullptr;
		}

		static PostEffectManager* GetInstance() { return m_instance; };

		/// @brief �e��ݒ���I���ɂ��邩�ǂ�������́B
		/// @param bloomMode �u���[�����I���ɂ��邩?
		/// @param shadowMode 
		void Init(bool bloomMode, bool shadowMode);

		bool GetShadowFlag() { return m_shadowMode; };

		Texture& GetMainRenderTarget() { return m_mainRenderTarget.GetRenderTargetTexture(); }

		//Texture& GetShadowMap() { return m_shadowMap.GetRenderTargetTexture(); };

		//Texture& GetBlurShadowMap() { return m_shadowBlur.GetBokeTexture(); };

		Texture& GetSpotLightMap(int no) { return m_spotLightMap[no].GetRenderTargetTexture(); };

		Texture& GetClairvoyanceMap() {return m_clairvoyanceMap.GetRenderTargetTexture();}

		//�����_�����O�O�̏���
		void BeforeRender(RenderContext& rc);
		//�����_�����O��̏���
		void AfterRender(RenderContext& rc);

		void ShadowRender(RenderContext& rc);
		void EndShadowRender(RenderContext& rc);

		void SpotLightRender(RenderContext& rc, int no);
		void EndSpotLightRender(RenderContext& rc, int no);

		void ClairvoyanceRender(RenderContext& rc);
		void EndClairvoyanceRender(RenderContext& rc);
		
	private:
		RenderTarget m_mainRenderTarget;
		Sprite m_copyToFrameBufferSprite;//��ʂɕ\������ŏI���ʂ̃X�v���C�g

		//�u���[���֘A
		bool m_bloomMode = true;	//�u���[�����L�����ǂ���
		RenderTarget m_luminanceRenderTarget;
		Sprite m_luminanceSprite;	//�P�x���o�����X�v���C�g
		Sprite m_bokeLuminanceSprite;//�P�x���o�������̂Ƀu���[���������X�v���C�g
		GaussianBlur m_gaussianBlur[4];//�u���[

		bool m_shadowMode = false;	//�V���h�E���L�����ǂ���
		//RenderTarget m_shadowMap;
		RenderTarget m_spotLightMap[3];
		//GaussianBlur m_shadowBlur;
		RenderTarget m_clairvoyanceMap;
	};

}