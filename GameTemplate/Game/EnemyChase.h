#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyChase
		{
		public:
			~EnemyChase();
			void Init(Enemy* enemy);
			void ExecuteUpdate();
			void Chase();	//追跡処理
			void GoHiddenPos();	//隠れた場所へ向かう

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

