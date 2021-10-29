#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer : public IGameObject
		{
		public:
			bool Start();

			void Move();

			void ExecuteUpdate();

			void SetMovePos(Vector3 pos1, Vector3 pos2) { m_searchPos[0] = pos1; m_searchPos[1] = pos2; };

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;

			//仮の移動処理
			Vector3 m_searchPos[2] = { { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f} };
			bool m_searchFlag = false;
		};

	}
}