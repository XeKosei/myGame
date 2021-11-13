#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyChaseConstant;

		bool EnemyChase::Start()
		{
			return true;
		}

		//Enemy.cpp��Update()�ŌĂяo������
		void EnemyChase::ExecuteUpdate()
		{
			Chase();

			//���������ȓ��܂ŏk�܂�����A�U���Ɉڍs�B
			if ((m_enemy->GetEnemyMove()->GetTarget() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= ENEMY_CAN_ATTACK_DIS
				&& m_enemy->GetPlayer()->GetPlayerState() == nsPlayer::Player::enState_Normal)
			{
				//�G�l�~�[�����݂���Ԃɂ���
				m_enemy->SetEnemyState(Enemy::enState_Attack);
				//�v���C���[�����݂����Ԃɂ���
				m_enemy->GetPlayer()->SetPlayerState(nsPlayer::Player::enState_Bitten);
				//�v���C���[�����݂���Ă��鑊����A���̃G�l�~�[�ɐݒ�y
				m_enemy->GetPlayer()->GetPlayerBitten()->SetEnemy(m_enemy);
			}
		}

		void EnemyChase::Chase()
		{
			//�^�[�Q�b�g���v���C���[�̈ʒu�Ɏw��
			m_enemy->GetEnemyMove()->SetTarget(m_enemy->GetPlayer()->GetPlayerMove()->GetPosition());
			//�ړ����x���w��
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_DASH_SPEED);

			
		}				
	}
}