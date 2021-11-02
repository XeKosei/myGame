#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyStress : public IGameObject
		{
		public:
			void ExecuteUpdate();

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

			/// @brief �ꂵ��
			void Suffer();

			/// @brief �G�l�~�[�ɃX�g���X��������
			/// @param num ������l
			void AddStress(int num);

			/// @brief �G�l�~�[�̃X�g���X�����炷
			/// @param num ���炷�l
			void SubStress(int num);
		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			//�X�g���X�l
			int m_stressNum = 0;
		};
	}
}
