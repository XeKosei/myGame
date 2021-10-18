#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		void EnemySearchPlayer::ExecuteUpdate()
		{
			Vector3 targetPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
			Vector3 toTargetDir = targetPos - m_dir;


		}
	}
}