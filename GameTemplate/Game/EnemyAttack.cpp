#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyAttackConstant;
		bool EnemyAttack::Start()
		{
			//�U�����[�V�����̎��Ԃ�ݒ�B
			m_attackMotionCount = ATTACKMOTION_TIME;

			//�G�l�~�[�Ɋ��݂��ꑱ���鎞��
			m_enemyBiteCount = BITING_TIME;

			return true;
		}
		void EnemyAttack::ExecuteUpdate()
		{
			//Attack();
			switch (m_biteState)
			{
			case enBiteState_PreBite:
				PreBite();
				break;
			case enBiteState_Bite:
				Bite();
				break;
			case enBiteState_EndBite:
				EndBite();
				break;
			default:
				break;
			}
		}

		void EnemyAttack::Attack()
		{
			//�U���s���̎��Ԃ��J�E���g
			m_attackMotionCount--;

			//�U������̂��鎞�ԂȂ��
			if (m_attackMotionCount >= ATTACKMOTION_HIT_START_TIME
				&& m_attackMotionCount <= ATTACKMOTION_HIT_END_TIME)
			{
				//�v���C���[�ւ̃x�N�g��
				Vector3 toPlayerDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
				//�G�l�~�[�̌���
				Vector3 enemyDir = m_enemy->GetEnemyMove()->GetDirection();

				if (Dot(toPlayerDir, enemyDir) >= ATTACKMOTION_HIT_DOT && toPlayerDir.Length() <= ATTACKMOTION_HIT_DIS)
				{
					m_enemy->GetPlayer()->GetPlayerSanity()->Damage(0);
				}
			}
			//�J�E���g���I�������A�G�l�~�[�̏�Ԃ�ǐՃ��[�h�Ɉڍs���A���Z�b�g
			else if (m_attackMotionCount <= -50)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
				m_attackMotionCount = ATTACKMOTION_TIME;
			}		
		}

		//���݂��̍ŏ��̏���
		void EnemyAttack::PreBite()
		{
			//�G�l�~�[�̌�����ݒ�
			Vector3 dir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_enemy->GetEnemyModel()->SetRotation(qRot);

			//�A�j���[�V�������I������玟�̃X�e�b�v��
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_biteState = enBiteState_Bite;
			}
		}

		//���݂����̏���
		void EnemyAttack::Bite()
		{
			//���݂���鎞�Ԃ��J�E���g
			m_enemyBiteCount--;
			//�A�j���[�V�����̎��Ԃ��J�E���g
			m_enemyBiteAnimCount++;

			//�A�j���[�V���������݂����[�V�������Ȃ�A�_���[�W��^����B
			if (m_enemyBiteAnimCount == BITEANIM_BITE_TIMING)
			{
				m_enemy->GetPlayer()->GetPlayerSanity()->Damage(BITE_DAMAGE);
			}
			//�A�j���[�V������1���[�v������
			else if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				//�A�j���[�V�������J�E���g���Z�b�g
				m_enemyBiteAnimCount = 0;
				//�A�j���[�V���������Z�b�g���邽�߂ɁA��x�ʂ̃A�j���[�V����������(�㏑�������̂ł���͍Đ�����Ȃ��B)
				m_enemy->GetEnemyModel()->PlayAnimation(EnemyAnim::enAnimationClip_Idle);
			}

			//�J�E���g���I�������A���̃X�e�b�v�ֈڍs
			if (m_enemyBiteCount <= 0)
			{
				m_biteState = enBiteState_EndBite;
			}
		}

		//���݂��̏I�������̏���
		void EnemyAttack::EndBite()
		{
			//�A�j���[�V�������I�������A
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				//�G�l�~�[��ǐՏ�ԂɈڍs���āA���Z�b�g
				m_biteState = enBiteState_PreBite;
				m_enemy->SetEnemyState(Enemy::enState_Scream);
				m_enemyBiteCount = BITING_TIME;
				m_enemyBiteAnimCount = 0;
			}
		}
	}
}