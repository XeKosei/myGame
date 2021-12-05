#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyStress : public IGameObject
		{
		public:
			~EnemyStress();
			void Init(Enemy* enemy);
			void ExecuteUpdate();

			/// @brief 苦しむ
			void Suffer();

			/// @brief エネミーにストレスを加える
			/// @param num 加える値
			void AddStress(int num);

			/// @brief エネミーのストレスを減らす
			/// @param num 減らす値
			void SubStress(int num);
		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//ストレス値
			int m_stressNum = 0;
			//前フレームでのストレス値
			int m_oldStressNum = 0;
		};
	}
}

