#include "stdafx.h"
#include "Playerinclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
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
			Vector3 dir = m_enemy->GetEnemyChase()->GetPosition() - m_player->GetPlayerMove()->GetPosition();
			float angle = atan2(dir.x, dir.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, angle);
			m_player->GetPlayerModel()->SetRotation(qRot);
		}
		void PlayerBitten::Bitten()
		{

		}
		void PlayerBitten::EndBitten()
		{

		}

	}
}