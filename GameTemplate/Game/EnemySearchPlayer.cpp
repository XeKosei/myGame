#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemySearchPlayerConstant;

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//エネミーの位置からプレイヤーの位置へのベクトルを求める
			Vector3 toTargetDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_position;
			toTargetDir.Normalize();

			//エネミーの向きとの内積が一定以上なら、プレイヤーを追いかけ始める。
			if (Dot(toTargetDir, nsEnemyConstant::INI_ENEMY_DIRECTION) >= 0.9f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
			}
		}
	}
}