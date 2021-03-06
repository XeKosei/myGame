#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyConstant;

		EnemyVigilant::~EnemyVigilant()
		{

		}

		void EnemyVigilant::Init(Enemy* enemy)
		{
			m_enemy = enemy;
		}

		void EnemyVigilant::ExecuteUpdate()
		{
			//移動速度をリセット
			m_enemy->GetEnemyMove()->ResetVelocity();

			//エネミーの位置からプレイヤーの位置へのベクトルを求める
			Vector3 toPlayerDis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();

			if (toPlayerDis.Length() <= ENEMY_SEARCH_DIS)
			{
				m_calcLineHitModelConstant--;

				if (m_calcLineHitModelConstant <= 0)
				{
					m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;

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
						m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;

						startPos.y -= 10.0f;
						endPos.y -= 10.0f;
						m_enemy->SetEnemyState(Enemy::enState_Scream);
						m_enemy->GetEnemyMove()->RouteSearch(startPos, endPos);
						m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_Straight);

						SoundSource* ss = NewGO<SoundSource>(0);
						ss->Init(L"Assets/sound/EnemyFoundPlayer.wav");
						ss->Play(false);
					}
				}
			}
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_SearchPlayer);
				m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_RouteSearch);
				m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;
				m_enemy->GetEnemySearchPlayer()->CalcNextSearchPos();
				m_enemy->GetEnemyMove()->RouteSearch(m_enemy->GetEnemyMove()->GetPosition(), m_enemy->GetEnemySearchPlayer()->GetTargetSearchPos());
			}
		}
	}
}