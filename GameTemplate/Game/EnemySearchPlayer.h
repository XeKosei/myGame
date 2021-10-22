#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer : public IGameObject
		{
		public:
			bool Start();

			void ExecuteUpdate();

			void Move();

			void Turn();

			void SetMovePos(Vector3 pos1, Vector3 pos2) { m_searchPos[0] = pos1; m_searchPos[1] = pos2; };

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

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
			Vector3 m_dir = { -1.0f, 0.0f, 0.0f };
			//��]
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//�G�l�~�[���������ʒu
			Vector3 m_targetPos = { Vector3::Zero };

			//���̈ړ�����
			Vector3 m_searchPos[2] = { { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f} };
			bool m_searchFlag = false;
		};

	}
}