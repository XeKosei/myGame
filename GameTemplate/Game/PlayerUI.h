#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerUI : public IGameObject
		{
		public:
			~PlayerUI();
			bool Start();
			void ExecuteUpdate();

			//Hazyスプライトを設定する
			void SetHazySprite();

			//スプライトの点滅処理
			void BlinkHazySprite();

			//死んだとき
			void DyingHazySprite();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//プレイヤー
			Player* m_player = nullptr;

			//ダメージを受けた際の画面の周りのスプライト
			SpriteRender* m_hazySprite = nullptr;
			//hazyスプライト関連
			//スプライトの色
			Vector4 m_hazyColor = { 0.0f,0.0f,0.0f,0.0f };
			//スプライトの点滅
			float m_addAlpha = 0.0f;
			bool m_addAlphaFlag = true;
		};
	}
}

