#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemySearchPlayerConstant;

		bool EnemySearchPlayer::Start()
		{
			//初期位置を指定
			m_enemy->GetEnemyMove()->SetPosition(m_searchPos[0]);
			return true;
		}

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//移動処理(仮)
			Search();

			//エネミーの位置からプレイヤーの位置へのベクトルを求める
			Vector3 toPlayerDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
			toPlayerDir.Normalize();

			//エネミーの向きとの内積が一定以上なら、プレイヤーを追いかけ始める。
			if (Dot(toPlayerDir, m_enemy->GetEnemyMove()->GetDirection()) >= 0.9f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Scream);
			}
		}

		void EnemySearchPlayer::Search()
		{
			//指定した二か所の位置を往復する処理

			//エネミーの移動の速さを設定
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_WALK_SPEED);

			//エネミーが向かう位置を設定する。
			if (m_searchFlag == false)
			{
				m_enemy->GetEnemyMove()->SetTarget(m_searchPos[1]);		
			}
			else
			{
				m_enemy->GetEnemyMove()->SetTarget(m_searchPos[0]);
			}

			//エネミーの位置がほぼターゲットと一緒になったら、
			if ((m_enemy->GetEnemyMove()->GetTarget() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= 5.0f)
			{
				m_searchFlag = !m_searchFlag;
			}

		}
	}
}