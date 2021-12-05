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
			void Chase();	//�ǐՏ���
			void GoHiddenPos();	//�B�ꂽ�ꏊ�֌�����

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			//���C���΂��Ԋu
			int m_calcLineHitModelConstant = 0;

			//�v���C���[���B��Ă��邩�ǂ���
			bool m_isPlayerHidden = false;
		};
	}
}

