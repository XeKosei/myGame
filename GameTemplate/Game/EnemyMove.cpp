#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "TknFile.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyMoveConstant;

		bool EnemyMove::Start()
		{
			// �i�r���b�V�����\�z�B
			m_nvmMesh.Init("Assets/nvm/nvmTest.tkn");
			return true;
		}

		void EnemyMove::ExecuteUpdate()
		{
			//Move();
			Turn();

			RouteSearchMove();
		}

		void EnemyMove::Move()
		{
			//�^�[�Q�b�g�ƃG�l�~�[�Ƃ̃x�N�g�����v�Z�B
			m_direction = m_targetPos - m_position;
			m_direction.Normalize();

			//�ړ�����
			if (m_slowMoveFlag == false)
				m_velocity = m_direction * m_moveSpeed;
			else
				m_velocity = m_direction * ENEMY_SLOWWALK_SPEED;

			m_velocity *= GameTime::GetInstance().GetFrameDeltaTime();

			//��������
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			//�d��
			if (m_enemy->GetCharaCon()->IsOnGround() == false)
			{	//�n�ʂɂ��Ă��Ȃ�������
				m_velocity.y -= pow(GRAVITY_SPEED, GRAVITY_INDEX);	//�d�͂�^����
			}

			//���x���ق�0�Ȃ�΁A0�ɂ���B
			if (fabsf(m_velocity.x + m_velocity.z) < 0.001f)
			{
				m_velocity.x = 0.0f;
				m_velocity.z = 0.0f;
			}

			//�ʒu�ɑ��x�����Z
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);

			//�^�[�Q�b�g�n�_�ɂقړ��B������A
			if ((m_position - m_targetPos).Length() < 5.0f)
			{
				m_position = m_targetPos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
			}
			
			//���f���ʒu��ݒ肷��B
			m_enemy->GetEnemyModel()->SetPosition(m_position);	
		}

		//�o�H�T���ŁA���𒲂ׂ鏈��
		void EnemyMove::RouteSearch(Vector3 pos, Vector3 targetPos)
		{
			m_targetPos = targetPos;
			// �p�X����
			m_pathFiding.Execute(
				m_path,							// �\�z���ꂽ�p�X�̊i�[��
				m_nvmMesh,						// �i�r���b�V��
				pos,						// �J�n���W
				targetPos,					// �ړ��ڕW���W
				PhysicsWorld::GetInstance(),	// �����G���W��	
				10.0f,							// AI�G�[�W�F���g�̔��a
				120.0f							// AI�G�[�W�F���g�̍����B
			);
		}

		//�o�H�T���ł̈ړ�����
		void EnemyMove::RouteSearchMove()
		{
			/*if (g_pad[0]->IsTrigger(enButtonA))
			{
				QueryGOs<nsBackGround::BackGround>("backGround", [this](nsBackGround::BackGround* backGround)->bool {
					Vector3 pos = Vector3::Zero;
					Vector3 startPos = m_position;
					startPos.y += 10.0f;
					Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
					endPos.y += 10.0f;

					if (backGround->GetStageModel()->isLineHitModel(startPos, endPos, pos) == false)
					{
						m_enemy->SetEnemyState(Enemy::enState_Scream);
					}
					return true;
					}
				);
			}*/

			Vector3 oldPos = m_position;

			bool isEnd;		
			
			//�p�X����ړ�����B
			m_position = m_path.Move(
				m_position,
				5.0f,
				isEnd
			);

			//�����Ƒ��x
			m_velocity = m_position - oldPos;
			m_direction = m_velocity;
			m_direction.Normalize();

			//�ʒu��ݒ�
			m_enemy->GetEnemyMove()->SetPosition(m_position);
		}

		void EnemyMove::Turn()
		{
			if (m_velocity.x != 0.0f || m_velocity.z != 0.0f)
			{
				//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
				//m_direction.x / m_direction.z�̌��ʂ�tan�ƂɂȂ�B
				//atan2���g�p���āA�p�x�����߂Ă���B
				//���ꂪ��]�p�x�ɂȂ�B
				float angle = atan2(m_direction.x, m_direction.z);
				//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
				//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_enemy->GetEnemyModel()->SetRotation(m_qRot);
			}
		}
	}
}