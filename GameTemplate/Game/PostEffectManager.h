#pragma once
#include "GaussianBlur.h"
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

	Texture& GetShadowMap() { return m_shadowMap.GetRenderTargetTexture(); };

	//Texture& GetBlurShadowMap() { return m_shadowBlur.GetBokeTexture(); };

	//�����_�����O�O�̏���
	void BeforeRender(RenderContext& rc);
	//�����_�����O��̏���
	void AfterRender(RenderContext& rc);

	void ShadowRender(RenderContext& rc);
	void EndShadowRender(RenderContext& rc);

private:
	RenderTarget m_mainRenderTarget;
	Sprite m_copyToFrameBufferSprite;//��ʂɕ\������ŏI���ʂ̃X�v���C�g

	//�u���[���֘A
	bool m_bloomMode = true;	//�u���[�����L�����ǂ���
	RenderTarget m_luminanceRenderTarget;
	Sprite m_luminanceSprite;	//�P�x���o�����X�v���C�g
	Sprite m_bokeLuminanceSprite;//�P�x���o�������̂Ƀu���[���������X�v���C�g
	GaussianBlur m_gaussianBlur[4];//�u���[

	bool m_shadowMode = true;	//�V���h�E���L�����ǂ���
	RenderTarget m_shadowMap;
	GaussianBlur m_shadowBlur;
};

