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
			//動けるようになるまでのインターバルを設定。
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
			//プレイヤーの向きを設定。
			Vector3 dir = m_enemy->GetEnemyChase()->GetPosition() - m_player->GetPlayerMove()->GetPosition();
			dir.Normalize();
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);
			m_player->GetPlayerCamera()->SetCameraDir(dir);

			//エネミーの噛みつきが次のステップへ移行したら、プレイヤーも次のステップへ移行
			if (m_enemy->GetEnemyAttack()->GetBiteState() == nsEnemy::EnemyAttack::enBiteState_Bite)
			{
				SetBittenState(enBittenState_Bitten);
			}
		}
		void PlayerBitten::Bitten()
		{
			//BボタンかAボタン連打で抵抗する。
			if (g_pad[0]->IsTrigger(enButtonB) || g_pad[0]->IsTrigger(enButtonA))
			{
				m_enemy->GetEnemyAttack()->RegistToBite(RESIST_TO_BITE_NUM);
			}

			//エネミーの噛みつきが次のステップへ移行したら、プレイヤーも次のステップへ移行
			if (m_enemy->GetEnemyAttack()->GetBiteState() == nsEnemy::EnemyAttack::enBiteState_EndBite)
			{
				SetBittenState(enBittenState_EndBitten);
			}
		}
		void PlayerBitten::EndBitten()
		{
			//動けるようになるまでのインターバル
			m_canMoveInterval--;
			//インターバルが終わったら、リセットして、動けるようになる。
			if (m_canMoveInterval <= 0)
			{
				m_canMoveInterval = INI_CAN_MOVE_INTERVAL;
				SetBittenState(enBittenState_PreBitten);
				m_player->SetInvincible(200);
			}
		}

	}
}