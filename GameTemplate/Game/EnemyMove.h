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

			void Move();

			void Turn();

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

			void SetPosition(Vector3 pos) { 
				m_position = pos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
				m_enemy->GetEnemyModel()->SetPosition(m_position);
			}

			/// @brief Enemy��m_position���擾
			/// @return �G�l�~�[�̈ʒu
			Vector3 GetPosition() { return m_position; };

			/// @brief Enemy�̌������擾�B
			/// @return �G�l�~�[�̌���
			Vector3 GetDirection() { return m_direction; }

			/// @brief Enemy�̈ړ����x���擾
			/// @return �G�l�~�[�̈ړ����x
			Vector3 GetVelocity() { return m_velocity; }

			/// @brief �G�l�~�[���������ʒu��ݒ�
			/// @param pos �G�l�~�[���������ʒu
			void SetTarget(Vector3 pos) { m_targetPos = pos; }

			/// @brief �G�l�~�[�̃^�[�Q�b�g�ʒu���擾����B
			/// @return �G�l�~�[�̃^�[�Q�b�g�ʒu
			Vector3 GetTarget() { return m_targetPos; }

			/// @brief �G�l�~�[�̈ړ��̑������擾
			/// @param speed �G�l�~�[�̈ړ��̑���
			void SetMoveSpeed(float speed) { m_moveSpeed = speed; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			//�ʒu
			Vector3 m_position = { Vector3::Zero };
			//�G�l�~�[����������
			float m_moveSpeed = 0.0f;
			//���x
			Vector3 m_velocity = { Vector3::Zero };
			//����
			Vector3 m_direction = { 0.0f, 0.0f, 0.0f };
			//��]
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//�G�l�~�[���������ʒu
			Vector3 m_targetPos = { Vector3::Zero };
		};

	}
}