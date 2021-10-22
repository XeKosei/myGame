#include "stdafx.h"
#include "Playerinclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerBittenConstant;

		bool PlayerBitten::Start()
		{
			m_bittenStates = enBittenState_PreBitten;
			//������悤�ɂȂ�܂ł̃C���^�[�o����ݒ�B
			m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
			return true;
		}
		void PlayerBitten::ExecuteUpdate()
		{
			switch (m_bittenStates)
			{
			case enBittenState_PreBitten:
				PreBitten();
				break;
			case enBittenState_Bitten:
				Bitten();
				break;
			case enBittenState_EndBitten:
				EndBitten();
				break;
			default:
				break;
			}
		}
		void PlayerBitten::PreBitten()
		{
			//�v���C���[�̌�����ݒ�B
			Vector3 dir = m_enemy->GetEnemyChase()->GetPosition() - m_player->GetPlayerMove()->GetPosition();
			dir.Normalize();
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);
			m_player->GetPlayerCamera()->SetCameraDir(dir);

			//�G�l�~�[�̊��݂������̃X�e�b�v�ֈڍs������A�v���C���[�����̃X�e�b�v�ֈڍs
			if (m_enemy->GetEnemyAttack()->GetBiteState() == nsEnemy::EnemyAttack::enBiteState_Bite)
			{
				SetBittenState(enBittenState_Bitten);
			}
		}
		void PlayerBitten::Bitten()
		{
			//B�{�^����A�{�^���A�łŒ�R����B
			if (g_pad[0]->IsTrigger(enButtonB) || g_pad[0]->IsTrigger(enButtonA))
			{
				m_enemy->GetEnemyAttack()->RegistToBite(RESIST_TO_BITE_NUM);
			}

			//�G�l�~�[�̊��݂������̃X�e�b�v�ֈڍs������A�v���C���[�����̃X�e�b�v�ֈڍs
			if (m_enemy->GetEnemyAttack()->GetBiteState() == nsEnemy::EnemyAttack::enBiteState_EndBite)
			{
				SetBittenState(enBittenState_EndBitten);
			}
		}
		void PlayerBitten::EndBitten()
		{
			//������悤�ɂȂ�܂ł̃C���^�[�o��
			m_canMoveInterval--;
			//�C���^�[�o�����I�������A���Z�b�g���āA������悤�ɂȂ�B
			if (m_canMoveInterval <= 0)
			{
				m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
				SetBittenState(enBittenState_PreBitten);
				m_player->SetInvincible(200);
			}
		}

	}
}