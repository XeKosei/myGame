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
			int m_HP = 0.0f;

		};
	}
}