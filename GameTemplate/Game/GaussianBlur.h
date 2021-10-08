#pragma once
namespace nsHikageri
{
	class GaussianBlur
	{
	public:
		/// @brief 初期化
		/// @param originalTexture ガウシアンブラーをかけるオリジナルのテクスチャ
		void Init(Texture* originalTexture);

		/// @brief ガウシアンブラーをGPU上で実行。
		/// <remarks>
		/// 本関数の呼び出しは、DirectX12を利用した描画コマンド生成中に呼び出す必要があります。
		/// </remarks>
		/// @param rc レンダリングターゲット
		/// @param blurPower ブラーの強さ。値が大きければ大きい程ボケが強くなる。
		void ExecuteOnGPU(RenderContext& rc, float blurPower);

		/// @brief ボケテクスチャを取得
		Texture& GetBokeTexture()
		{
			return m_yBlurRenderTarget.GetRenderTargetTexture();
		}

	private:
		/// @brief レンダリングターゲットを初期化
		void InitRenderTargets();

		/// @brief スプライトの初期化
		void InitSprites();

		/// @brief 重みテーブルを更新する。
		void UpdateWeightsTable(float blurPower);

		enum { NUM_WEIGHTS = 8 };				//重みの数。
		float m_weights[NUM_WEIGHTS];			//重みテーブル
		Texture* m_originalTexture = nullptr;	//オリジナルテクスチャ
		RenderTarget m_xBlurRenderTarget;		//横ボケ画像を描画するレンダリングターゲット
		RenderTarget m_yBlurRenderTarget;		//縦ボケ画像を描画するレンダリングターゲット
		Sprite m_xBlurSprite;					//横ボケ画像を描画するためのスプライト
		Sprite m_yBlurSprite;					//縦ボケ画像を描画するためのスプライト
	};

}