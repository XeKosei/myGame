#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }

	namespace nsGimmick
	{
		class Chandelier : public IGameObject
		{
		public:
			~Chandelier();
			bool Start();
			void Update();

			void SetPosition(Vector3 pos) { m_position = pos; };

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			SkinModelRender* m_chandelierModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			//プレイヤーとエネミー
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;
		};
	}
}