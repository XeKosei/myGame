#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyMove : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();
			void Move();	//�ړ�����
			void Turn();	//��]����

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* pl) { m_enemy = pl; };

			/// @brief �G�l�~�[���������ʒu��ݒ�
			/// @param pos �G�l�~�[���������ʒu
			void SetTarget(Vector3 pos) { m_targetPos = pos; }

		private:
			//�ʒu
			Vector3 m_position = { Vector3::Zero };
			//�G�l�~�[����������
			float m_moveSpeed = 0.0f;
			//���x
			Vector3 m_velocity = { Vector3::Zero };
			//��]
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//�G�l�~�[���������ʒu
			Vector3 m_targetPos = {Vector3::Zero};
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
		};
	}
}

