#include "stdafx.h"
#include "PostEffectManager.h"

namespace nsHikageri
{
	PostEffectManager* PostEffectManager::m_instance = nullptr;

	void PostEffectManager::Init(bool bloomMode, bool shadowMode)
	{
		m_bloomMode = bloomMode;
		m_shadowMode = shadowMode;

		//最終的に画面に出力する用のレンダーターゲット
		m_mainRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		if (m_bloomMode == true)
		{
			//輝度を抽出したものが格納されるレンダリングターゲット
			m_luminanceRenderTarget.Create(
				1280,
				720,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			//ピクセルシェーダーPSSamplingLuminanceで、メインレンダーターゲットから輝度を抽出するためのスプライト
			SpriteInitData luminanceSpriteInitData;
			luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
			luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
			luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
			luminanceSpriteInitData.m_width = 1280;
			luminanceSpriteInitData.m_height = 720;
			luminanceSpriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
			luminanceSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

			m_luminanceSprite.Init(luminanceSpriteInitData);

			//輝度抽出したスプライトをもとにブラーをかけさせるようにセット。
			m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());
			m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
			m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
			m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

			//輝度抽出されたものにブラーをかけたスプライト
			//ピクセルシェーダーPSSamplingLuminanceで、メインレンダーターゲットから輝度を抽出するためのスプライト
			SpriteInitData bokeLuminanceSpriteInitData;
			bokeLuminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
			bokeLuminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
			bokeLuminanceSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
			bokeLuminanceSpriteInitData.m_width = 1280;
			bokeLuminanceSpriteInitData.m_height = 720;
			bokeLuminanceSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
			bokeLuminanceSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
			bokeLuminanceSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
			bokeLuminanceSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
			bokeLuminanceSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();
			bokeLuminanceSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

			m_bokeLuminanceSprite.Init(bokeLuminanceSpriteInitData);
		}

		//if (m_shadowMode)
		//{
		//	//シャドウマップの作成
		//	float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		//	m_shadowMap.Create(
		//		2048,
		//		2048,
		//		1,
		//		1,
		//		DXGI_FORMAT_R32G32_FLOAT,
		//		DXGI_FORMAT_D32_FLOAT,
		//		clearColor
		//	);
		//	//VSM用にテクスチャをぼかす。
		//	m_shadowBlur.Init(&m_shadowMap.GetRenderTargetTexture());
		//}

		//スポットライト用のマップの作成
		for (int no = 0; no < 3; no++)
		{
			m_spotLightMap[no].Create(
				1028,
				720,
				1,
				1,
				DXGI_FORMAT_R32G32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);
			//VSM用にテクスチャをぼかす。
			m_spotLightMapBlur[no].Init(&m_spotLightMap[no].GetRenderTargetTexture());
		}

		//透視用のマップ
		m_clairvoyanceMap.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//最終的な画面に出力されるスプライト
		SpriteInitData copyToBufferSpriteInitData;
		copyToBufferSpriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		copyToBufferSpriteInitData.m_width = 1280;
		copyToBufferSpriteInitData.m_height = 720;
		copyToBufferSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyToFrameBufferSprite.Init(copyToBufferSpriteInitData);

	}

	void PostEffectManager::ShadowRender(RenderContext& rc)
	{
		/*if (m_shadowMode)
		{
			rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
			rc.SetRenderTargetAndViewport(m_shadowMap);
			rc.ClearRenderTargetView(m_shadowMap.GetRTVCpuDescriptorHandle(), m_shadowMap.GetRTVClearColor());
			rc.ClearDepthStencilView(m_shadowMap.GetDSVCpuDescriptorHandle(), m_shadowMap.GetDSVClearValue());

			D3D12_RECT shadowRect;
			shadowRect.left = 0;
			shadowRect.top = 0;
			shadowRect.right = 2048;
			shadowRect.bottom = 2048;
			rc.SetScissorRect(shadowRect);
		}*/
	}
	void PostEffectManager::EndShadowRender(RenderContext& rc)
	{
		/*if (m_shadowMode)
		{
			rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

			m_shadowBlur.ExecuteOnGPU(rc, 5.0f);

			D3D12_RECT normalRect;
			normalRect.left = 0;
			normalRect.top = 0;
			normalRect.right = 1280;
			normalRect.bottom = 720;
			rc.SetScissorRect(normalRect);
		}*/
	}

	void PostEffectManager::SpotLightRender(RenderContext& rc, int no)
	{
		rc.WaitUntilToPossibleSetRenderTarget(m_spotLightMap[no]);
		rc.SetRenderTargetAndViewport(m_spotLightMap[no]);
		rc.ClearRenderTargetView(m_spotLightMap[no].GetRTVCpuDescriptorHandle(), m_spotLightMap[no].GetRTVClearColor());
		rc.ClearDepthStencilView(m_spotLightMap[no].GetDSVCpuDescriptorHandle(), m_spotLightMap[no].GetDSVClearValue());
	}
	void PostEffectManager::EndSpotLightRender(RenderContext& rc, int no)
	{
		rc.WaitUntilFinishDrawingToRenderTarget(m_spotLightMap[no]);
		//m_spotLightMapBlur[no].ExecuteOnGPU(rc, 5.0f);
	}

	void PostEffectManager::ClairvoyanceRender(RenderContext& rc)
	{
		rc.WaitUntilToPossibleSetRenderTarget(m_clairvoyanceMap);
		rc.SetRenderTargetAndViewport(m_clairvoyanceMap);
		rc.ClearRenderTargetView(m_clairvoyanceMap.GetRTVCpuDescriptorHandle(), m_clairvoyanceMap.GetRTVClearColor());
		rc.ClearDepthStencilView(m_clairvoyanceMap.GetDSVCpuDescriptorHandle(), m_clairvoyanceMap.GetDSVClearValue());
	}
	void PostEffectManager::EndClairvoyanceRender(RenderContext& rc)
	{
		rc.WaitUntilFinishDrawingToRenderTarget(m_clairvoyanceMap);
	}

	//レンダリング前の処理
	void PostEffectManager::BeforeRender(RenderContext& rc)
	{
		//メインレンダリングターゲットを描画先にセットする。
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget.GetRTVCpuDescriptorHandle(), m_mainRenderTarget.GetRTVClearColor());
		rc.ClearDepthStencilView(m_mainRenderTarget.GetDSVCpuDescriptorHandle(), m_mainRenderTarget.GetDSVClearValue());
		//この後、各モデルのドローコールが呼ばれる(はず)。
	}
	//レンダリング後の処理
	void PostEffectManager::AfterRender(RenderContext& rc)
	{
		//メインレンダーターゲットが描画を終えるまで待つ。
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

		if (m_bloomMode == true)
		{
			//輝度抽出用のレンダーターゲットに変更する。
			rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
			rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
			rc.ClearRenderTargetView(m_luminanceRenderTarget.GetRTVCpuDescriptorHandle(), m_luminanceRenderTarget.GetRTVClearColor());
			//輝度抽出を行う
			m_luminanceSprite.Draw(rc);
			//輝度抽出用のレンダーターゲットが描画を終えるまで待つ。
			rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);

			//ガウシアンブラーを実行する。
			m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
			m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
			m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
			m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

			//メインレンダーターゲットが使えるようになるまで待つ。
			rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
			rc.SetRenderTargetAndViewport(m_mainRenderTarget);
			//この輝度抽出したものをぼかしたものをメインレンダーターゲットに加算合成
			//この時点でメインレンダーターゲットには元の画像とブラーの画像が合わさったものになる。
			m_bokeLuminanceSprite.Draw(rc);
			//メインレンダーターゲットが描画を終えるまで待つ。
			rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
		}

		//描画先をフレームバッファにする。
		rc.SetRenderTarget(g_graphicsEngine->GetCurrentFrameBuffuerRTV(), g_graphicsEngine->GetCurrentFrameBuffuerDSV());

		//メインレンダーターゲットに描かれていた最終イメージを画面上に描く。
		m_copyToFrameBufferSprite.Draw(rc);
	}
}
