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

			void BloodSprite();

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

			Vector4 m_bloodColor = {0.0f,0.0f,0.0f,0.0f};
			float m_addRed = 0.0f;
			bool m_addRedFlag = true;
		};
	}
}