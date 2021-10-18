#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer : public IGameObject
		{
		public:
			void ExecuteUpdate();
			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;

			Vector3 m_position = Vector3::Zero;

			Vector3 m_dir = {0.0f, 0.0f, 1.0f};

		};

	}
}