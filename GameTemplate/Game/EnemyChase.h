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
			void Chase();	//�ǐՏ���
			void GoHiddenPos();	//�B�ꂽ�ꏊ�֌�����

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

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

