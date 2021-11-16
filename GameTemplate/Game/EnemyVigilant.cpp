#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyConstant;

		void EnemyVigilant::ExecuteUpdate()
		{
			//エネミーの位置からプレイヤーの位置へのベクトルを求める
			Vector3 toPlayerDis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();

			if (toPlayerDis.Length() <= ENEMY_SEARCH_DIS)
			{
				m_calcLineHitModelConstant--;

				if (m_calcLineHitModelConstant <= 0)
				{
					m_calcLineHitModelConstant = CALC_LINEHITMODEL_COSNTANT;

					Vector3 toPlayerDir = toPlayerDis;
					toPlayerDir.Normalize();

					Vector3 startPos = m_enemy->GetEnemyMove()->GetPosition();
					startPos.y += 10.0f;	//地面との接触をなくすために少し浮かせる
					Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
					endPos.y += 10.0f;
					Vector3 hitPos = Vector3::Zero;

					//エネミーの向きとの内積が一定以上なら、プレイヤーを追いかけ始める。
					if (Dot(toPlayerDir, m_enemy->GetEnemyMove()->GetDirection()) >= 0.7f
						&& m_enemy->GetBackGround()->GetStageModel()->isLineHitModel(startPos, endPos, hitPos) == false)
					{
						m_calcLineHitModelConstant = CALC_LINEHITMODEL_COSNTANT;

						startPos.y -= 10.0f;
						endPos.y -= 10.0f;
						m_enemy->SetEnemyState(Enemy::enState_Scream);
						m_enemy->GetEnemyMove()->RouteSearch(startPos, endPos);
						m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_Straight);
					}
				}
			}
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_SearchPlayer);
				m_calcLineHitModelConstant = CALC_LINEHITMODEL_COSNTANT;
				//m_enemy->GetEnemySearchPlayer()->CalcNextSearchPos();
				m_enemy->GetEnemyMove()->RouteSearch(m_enemy->GetEnemyMove()->GetPosition(), m_enemy->GetEnemySearchPlayer()->GetTargetSearchPos());
			}
		}
	}
}