#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyChase : public IGameObject
		{
		public:
			~EnemyChase();
			bool Start();
			void ExecuteUpdate();
			void Chase();	//追跡処理
			void GoHiddenPos();	//隠れた場所へ向かう

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//レイを飛ばす間隔
			int m_calcLineHitModelConstant = 0;

			//プレイヤーが隠れているかどうか
			bool m_isPlayerHidden = false;
		};
	}
}

