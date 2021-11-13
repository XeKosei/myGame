#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"
#include "TknFile.h"
namespace nsHikageri
{
	namespace nsAI { class NaviMesh; class Path; class PathFinding; };
	namespace nsEnemy
	{
		class Enemy;
		class EnemyMove : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			void Move();
			//�o�H�T���ł̈ړ�����
			void RouteSearchMove();

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

			/// @brief �������x���Ȃ��Ă��邩�ǂ����̃t���O���擾����
			/// @return �������x���Ȃ��Ă��邩�ǂ���
			bool GetSlowMoveFlag() { return m_slowMoveFlag; };
			/// @brief �������x���Ȃ邩�ǂ���
			/// @param flag true:�x���Ȃ�@false:�x���Ȃ�Ȃ�
			void SetSlowMoveFlag(bool flag) { m_slowMoveFlag = flag; }

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

			//�������x���Ȃ邩�ǂ����̃t���O
			bool m_slowMoveFlag = false;	

			//�o�H�T���֘A
			nsAI::NaviMesh m_nvmMesh;
			nsAI::Path m_path;
			nsAI::PathFinding m_pathFiding;
			TknFile m_tknFile;
			int m_pathFindingInterval = 0;
		};

	}
}