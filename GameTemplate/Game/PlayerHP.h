#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerHP : public IGameObject
		{
		public:
			bool Start();

			void ExecuteUpdate();

			void SetBloodSprite();

			void BloodSpriteBlink();

			void GameOver();//仮

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief プレイヤーのダメージを指定した値だけ減らす。
			/// @param damageNum 与えるダメージ
			void Damage(int damageNum);
			
		private:
			//プレイヤー
			Player* m_player = nullptr;
			//プレイヤーの体力
			int m_HP = 0;
			//次にダメージを受けることができるようになるまでの間隔
			int m_damageIntervalCount = 0;
			//ダメージを受けた際の画面の周りの血の表現
			SpriteRender* m_bloodSprite = nullptr;

			//画面端の血のスプライト関連
			//血の色
			Vector4 m_bloodColor = {0.0f,0.0f,0.0f,0.0f};
			//血の点滅
			float m_addAlpha = 0.0f;
			bool m_addRedFlag = true;

			//HP表示(デバッグ用)
			FontRender* f = nullptr;


			FontRender* m_gameOverFont = nullptr;
			Vector4 m_gameOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
			Vector4 m_gameOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };
			int m_gameOverMoveCount = 250.0f;
		};
	}
}