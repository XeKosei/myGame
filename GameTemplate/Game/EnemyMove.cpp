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

		EnemyMove::~EnemyMove()
		{

		}

		void EnemyMove::Init(Enemy* enemy)
		{
			m_enemy = enemy;
			// �i�r���b�V�����\�z�B
			m_nvmMesh.Init("Assets/nvm/nvmTest.tkn");
		}

		void EnemyMove::ExecuteUpdate()
		{
			switch (m_moveState)
			{
			case enMoveState_Straight:
				Move();
				break;
			case enMoveState_RouteSearch:
				RouteSearchMove();
				break;
			};		

			Turn();
			FootStepsSE();
		}

		void EnemyMove::SetPosition(Vector3 pos) {
			m_position = pos;
			m_enemy->GetEnemyModel()->SetPosition(m_position);
			m_enemy->GetCharaCon()->SetPosition(m_position);
		}

		void EnemyMove::Move()
		{
		
			//�^�[�Q�b�g�ƃG�l�~�[�Ƃ̃x�N�g�����v�Z�B
			m_direction = m_targetPos - m_position;
			m_direction.Normalize();

			//�ړ�����
			if (m_slowMoveFlag)
			{
				m_moveSpeed = ENEMY_SLOWWALK_SPEED;
			}

			m_velocity += m_direction * m_moveSpeed * GameTime::GetInstance().GetFrameDeltaTime();

			//��������
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			m_direction = m_velocity;
			m_direction.Normalize();

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
			SetPosition(m_position);	
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
			Vector3 oldPos = m_position;

			bool isEnd;		
			
			//�ړ�����
			if (m_slowMoveFlag)
			{
				m_moveSpeed = ENEMY_SLOWWALK_SPEED;
			}

			//�p�X����ړ�����B
			Vector3 pathPos = m_path.Move(
				m_position,
				m_moveSpeed,
				isEnd
			);

			//�����Ƒ��x
			m_direction = pathPos - oldPos;
			m_direction.Normalize();

			m_velocity += m_direction * m_moveSpeed * GameTime::GetInstance().GetFrameDeltaTime();

			//��������
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			m_direction = m_velocity;
			m_direction.Normalize();

			//���x���ق�0�Ȃ�΁A0�ɂ���B
			if (fabsf(m_velocity.x + m_velocity.z) < 0.001f)
			{
				m_velocity.x = 0.0f;
				m_velocity.z = 0.0f;
			}

			//�ʒu�ɑ��x�����Z
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);

			//�p�X�̈ʒu�ɂقړ��B������A
			if (m_moveSpeed == ENEMY_DASH_SPEED && (m_position - pathPos).Length() < ENEMY_DASH_SPEED
			|| (m_moveSpeed == ENEMY_WALK_SPEED) && (m_position - pathPos).Length() < ENEMY_WALK_SPEED)
			{
				m_position = pathPos;
			}

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

		void EnemyMove::FootStepsSE()
		{
			//�����̊Ԋu
			m_footStepInterval--;

			if (m_footStepInterval < 0)
			{
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/EnemyFootStep.wav");	
				//�v���C���[�Ƃ̋�������A���ʂ�ݒ�
				float dis = (m_enemy->GetEnemyMove()->GetPosition() - m_enemy->GetPlayer()->GetPlayerMove()->GetPosition()).Length();
				m_footStepVolume = max(0.01f, 1.0f - dis * 0.0003f);
				ss->SetVolume(m_footStepVolume);
				ss->Play(false);

				if (m_slowMoveFlag)
				{
					m_footStepInterval = ENEMY_SLOWWALK_FOOTSTEP_INTERVAL;
				}
				else if (m_enemy->GetEnemyState() == Enemy::enState_SearchPlayer)
				{
					m_footStepInterval = ENEMY_WALK_FOOTSTEP_INTERVAL;
				}
				else if (m_enemy->GetEnemyState() == Enemy::enState_Chase)
				{
					m_footStepInterval = ENEMY_DASH_FOOTSTEP_INTERVAL;
				}
				else
				{
					m_footStepInterval = ENEMY_SLOWWALK_FOOTSTEP_INTERVAL;
				}


			}

			if (m_velocity.Length() == 0.0f)
			{
				m_footStepInterval = ENEMY_SLOWWALK_FOOTSTEP_INTERVAL;
			}
		}
	}
}