#include "stdafx.h"
#include "Playerinclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerBittenConstant;

		PlayerBitten::~PlayerBitten()
		{

		}

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

			//�G�̏�Ԃ����݂��ł͂Ȃ��Ȃ�����A
			if (m_enemy->GetEnemyState() != nsEnemy::Enemy::enState_Attack)
			{
				m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
				SetBittenState(enBittenState_PreBitten);
				m_player->SetInvincible(200);
			}
		}
		void PlayerBitten::PreBitten()
		{
			//�v���C���[�̃J�����̌�����ݒ�B
			Vector3 toEnemyDir = m_enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head") - m_player->GetPlayerCamera()->GetCameraPos();
			toEnemyDir.Normalize();
			Vector3 cameraDir = m_player->GetPlayerCamera()->GetDirection();
			//�G�l�~�[�ւ̌����ƁA�J�����̌����œ��ς����B
			float dot = Dot(toEnemyDir, cameraDir);

			//���ς̌��ʂɂ���āA�J�����̓������ω�
			Vector3 dir = m_player->GetPlayerCamera()->GetDirection();
			//�������قړ����Ȃ�A�����ɂ���B
			if (dot >= 0.99f)
			{
				dir = toEnemyDir;
			}
			//0�ȏ�Ȃ�A���炩�ɑ���ɐU�����
			else if(dot >= 0)
			{				
				dir += (toEnemyDir - cameraDir) * CAMERA_TURN_SPEED;
			}
			//0�ȉ��Ȃ�A�܂��J���������E�ɉ�]������B
			else
			{
				Vector3 enemyRight = Cross(toEnemyDir, Vector3::AxisY);
				//�E���������������Ȃ�E������
				if (Dot(enemyRight, cameraDir) >= 0)
				{
					dir += m_player->GetPlayerCamera()->GetCameraRight() * CAMERA_TURN_SPEED;
				}
				//�����������������Ȃ獶������
				else
				{
					dir += m_player->GetPlayerCamera()->GetCameraRight() * -CAMERA_TURN_SPEED;
				}
			}

			m_player->GetPlayerCamera()->SetCameraDir(dir);

			//���f���̌�����ݒ�B
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);

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

			//�v���C���[�J�����ƃ��f���̌�����ݒ�B
			Vector3 dir = m_enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head") - m_player->GetPlayerCamera()->GetCameraPos();
			dir.Normalize();
			m_player->GetPlayerCamera()->SetCameraDir(dir);

			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);
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